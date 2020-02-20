#include <QtGui>
#include <QDir>
#include <QClipboard>
#include <QDesktopServices>
#include <QImageWriter>
#include <QTextBlockUserData>
#include <QStack>
#include <QImage>
#include <QPixmap>
#include <QDialogButtonBox>
#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>
#include <QDockWidget>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QSplitter>

#include "TemplateExportDialog.h"

#include "SyntopiaCore/Misc/MiscDataCenter.h"

#include "MainWindow.h"
#include "VariableEditor.h"
#include "../Model/RandomStreams.h"
#include "../../SyntopiaCore/Logging/ListWidgetLogger.h"
#include "../../SyntopiaCore/Exceptions/Exception.h"
#include "../../StructureSynth/Parser/EisenParser.h"
#include "../../StructureSynth/Model/Rendering/OpenGLRenderer.h"
#include "../../StructureSynth/Model/Rendering/TemplateRenderer.h"
#include "../../StructureSynth/Model/Rendering/ObjRenderer.h"
#include "../../StructureSynth/Parser/Tokenizer.h"
#include "../../StructureSynth/Parser/Preprocessor.h"
#include "../../StructureSynth/Model/RuleSet.h"
#include "../../StructureSynth/Model/Builder.h"
#include "../../StructureSynth/JavaScriptSupport/JavaScriptParser.h"
#include "../../SyntopiaCore/GLEngine/Raytracer/RayTracer.h"
#include "../../SyntopiaCore/Math/Vector3.h"
#include "../../SyntopiaCore/Math/Random.h"
#include "../../SyntopiaCore/Math/Matrix4.h"

using namespace SyntopiaCore::Math;
using namespace SyntopiaCore::Logging;
using namespace StructureSynth::Model::Rendering;
using namespace SyntopiaCore::Exceptions;
using namespace StructureSynth::Parser;
using namespace StructureSynth::Model;
using namespace StructureSynth::JavaScriptSupport;
using namespace SyntopiaCore::GLEngine;

namespace StructureSynth {
	namespace GUI {

		namespace 
		{
			int MaxRecentFiles = 5;
		}

		namespace {
			void createCommandHelpMenu(QMenu* menu, QWidget* textEdit)
			{
				QMenu *raytraceMenu = new QMenu("Raytracer Commands", 0);
				raytraceMenu->addAction("set raytracer::ambient-occlusion-samples 0 // turn off AO", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::samples 4 // for anti-alias and DOF", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::dof [0.4,0.1] // focal-plane distance, strength", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::shadows false", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::reflection 0.5", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::phong [0.6,0.6,0.3]", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::size [800x600]", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::size [0x800] // auto-calc proper width", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::size [800x0] // auto-calc proper height", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::max-threads 2", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::light [0,0,-29]", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::voxel-steps 30", textEdit , SLOT(insertText()));
				raytraceMenu->addAction("set raytracer::max-depth 5", textEdit , SLOT(insertText()));
				
				QMenu *modifierMenu = new QMenu("Rule Modifiers", 0);
				modifierMenu->addAction("weight", textEdit , SLOT(insertText()));
				modifierMenu->addAction("maxdepth", textEdit , SLOT(insertText()));
				modifierMenu->addAction("maxdepth > newRule", textEdit , SLOT(insertText()));

				QMenu *transformationMenu = new QMenu("Transformations", 0);
				transformationMenu->addAction("x 1 // translations", textEdit , SLOT(insertText()));
				transformationMenu->addAction("y 1", textEdit , SLOT(insertText()));
				transformationMenu->addAction("z 1", textEdit , SLOT(insertText()));
				transformationMenu->addAction("rx 45 // rotate angle around x-axis", textEdit , SLOT(insertText()));
				transformationMenu->addAction("ry 45", textEdit , SLOT(insertText()));
				transformationMenu->addAction("rz 45", textEdit , SLOT(insertText()));
				transformationMenu->addAction("hue 0.9", textEdit , SLOT(insertText()));
				transformationMenu->addAction("sat 0.9", textEdit , SLOT(insertText()));
				transformationMenu->addAction("brightness 0.9", textEdit , SLOT(insertText()));
				transformationMenu->addAction("color white // static color", textEdit , SLOT(insertText()));
				transformationMenu->addAction("color random // use color pool", textEdit , SLOT(insertText()));
				transformationMenu->addAction("blend red 0.5 // blend color with strength 0.5", textEdit , SLOT(insertText()));
				transformationMenu->addAction("alpha 0.9 // make transparent", textEdit , SLOT(insertText()));
				transformationMenu->addAction("matrix ", textEdit , SLOT(insertText()));
				transformationMenu->addAction("size 2 // uniform scaling", textEdit , SLOT(insertText()));
				transformationMenu->addAction("size 1 1 1.2 // non-uniform scaling", textEdit , SLOT(insertText()));
				transformationMenu->addAction("reflect", textEdit , SLOT(insertText()));
				transformationMenu->addAction("fx // mirror in yz-plane", textEdit , SLOT(insertText()));
				transformationMenu->addAction("fy", textEdit , SLOT(insertText()));
				transformationMenu->addAction("fz", textEdit , SLOT(insertText()));

				QMenu *setMenu = new QMenu("Set Commands", 0);
				setMenu->addAction("set maxdepth 100", textEdit , SLOT(insertText()));
				setMenu->addAction("set maxobjects 100", textEdit , SLOT(insertText()));
				setMenu->addAction("set maxsize 10 // maximum object size", textEdit , SLOT(insertText()));
				setMenu->addAction("set minsize 0.1 // minimum object size", textEdit , SLOT(insertText()));
				setMenu->addAction("set background #fff", textEdit , SLOT(insertText()));
				setMenu->addAction("set seed 45", textEdit , SLOT(insertText()));

				QMenu *colorMenu = new QMenu("Set Colorpool Commands", 0);
				colorMenu->addAction("set colorpool randomrgb", textEdit , SLOT(insertText()));
				colorMenu->addAction("set colorpool randomhue", textEdit , SLOT(insertText()));
				colorMenu->addAction("set colorpool list:orange,yellow,blue // sample from list", textEdit , SLOT(insertText()));
				colorMenu->addAction("set colorpool image:test.png // sample from image", textEdit , SLOT(insertText()));

				QMenu *set2Menu = new QMenu("Exotic Set Commands", 0);
				set2Menu->addAction("set seed initial // reset random seed", textEdit , SLOT(insertText()));
				set2Menu->addAction("set recursion depth // traverse depth-first", textEdit , SLOT(insertText()));
				set2Menu->addAction("set rng old // old random generator", textEdit , SLOT(insertText()));
				set2Menu->addAction("set syncrandom true", textEdit , SLOT(insertText()));				

				QMenu *setCMenu = new QMenu("Camera Commands", 0);
				setCMenu->addAction("set scale 0.5", textEdit , SLOT(insertText()));
				setCMenu->addAction("set pivot [0 0 0]", textEdit , SLOT(insertText()));
				setCMenu->addAction("set translation [0 0 -20]", textEdit , SLOT(insertText()));
				setCMenu->addAction("set rotation  [1 0 0 0 1 0 0 0 1]", textEdit , SLOT(insertText()));
				setCMenu->addAction("set perspective-angle 70", textEdit , SLOT(insertText()));

				QMenu *pMenu = new QMenu("Preprocessor Commands", 0);
				pMenu->addAction("#define myAngle 45", textEdit , SLOT(insertText()));
				pMenu->addAction("#define angle 20 (float:0-90) // create slider with default value 20", textEdit , SLOT(insertText()));
				pMenu->addAction("#define iterations 20 (int:0-23) // create slider with default value 20", textEdit , SLOT(insertText()));

				QMenu *p2Menu = new QMenu("JavaScript Commands", 0);
				p2Menu->addAction("Builder.load(\"system.es\");", textEdit , SLOT(insertText()));
				p2Menu->addAction("Builder.define(\"_rotation\", 34);", textEdit , SLOT(insertText()));
				p2Menu->addAction("Builder.prepend(\"sometext\");", textEdit , SLOT(insertText()));
				p2Menu->addAction("Builder.append(\"sometext\");", textEdit , SLOT(insertText()));
				p2Menu->addAction("Builder.build();", textEdit , SLOT(insertText()));
				p2Menu->addAction("Builder.renderToFile(\"out.png\", overwrite);", textEdit , SLOT(insertText()));
				p2Menu->addAction("Builder.raytraceToFile(\"out.png\", overwrite);", textEdit , SLOT(insertText()));
				p2Menu->addAction("Builder.templateRenderToFile(\"Sunflow-Colored.rendertemplate\", \"sunflow.sc\", overwrite);", textEdit , SLOT(insertText()));
				p2Menu->addAction("Builder.execute('\"%JAVAPATH%/java\"', '-Xmx1G -server -jar \"%SUNFLOW%/sunflow.jar\" sunflow.sc -nogui -o sunflow.png\", true);", textEdit , SLOT(insertText()));
				p2Menu->addAction("Builder.reset();", textEdit , SLOT(insertText()));
				p2Menu->addAction("Builder.setSize(640,0);", textEdit , SLOT(insertText()));
				
				QAction* before = 0;
				if (menu->actions().count() > 0)
					before = menu->actions()[0];

				menu->insertMenu(before, modifierMenu);
				menu->insertMenu(before, transformationMenu);
				menu->insertMenu(before, setMenu);
				menu->insertMenu(before, set2Menu);
				menu->insertMenu(before, colorMenu);
				menu->insertMenu(before, raytraceMenu);
				menu->insertMenu(before, setCMenu);
				menu->insertMenu(before, pMenu);
				menu->insertMenu(before, p2Menu);
				menu->insertSeparator(before);

			}
		}

		void TextEdit::contextMenuEvent(QContextMenuEvent *event)
		{	
			QMenu *menu = createStandardContextMenu();

			createCommandHelpMenu(menu, this);

			menu->exec(event->globalPos());
			delete menu;
		}

		void TextEdit::insertText() {
			QString text = ((QAction*)sender())->text();
			insertPlainText(text.section("//",0,0)); // strip comments
		}


		class EisenScriptHighlighter : public QSyntaxHighlighter {
		public:

			EisenScriptHighlighter(QTextEdit* e) : QSyntaxHighlighter(e) {
				keywordFormat.setFontWeight(QFont::Bold);
				keywordFormat.setForeground(Qt::darkMagenta);
				bracketFormat.setFontWeight(QFont::Bold);
				bracketFormat.setForeground(Qt::blue);
				primitiveFormat.setFontWeight(QFont::Bold);
				primitiveFormat.setForeground(Qt::darkYellow);
				commentFormat.setForeground(Qt::darkGreen);
				warningFormat.setBackground(QBrush(Qt::yellow));
				preprocessorFormat.setForeground(QBrush(Qt::blue));
				preprocessorFormat.setFontWeight(QFont::Bold);

				expression = QRegExp("(set|blend|recursion|maxsize|minsize|translation|pivot|rotation|scale|maxobjects|background|color|rule|a|alpha|matrix|h|hue|sat|b|brightness|v|x|y|z|rx|ry|rz|s|fx|fy|fz|maxdepth|weight|md|w)");
				primitives = QRegExp("(triangle\\[.*\\]|sphere(::\\w+)?|box(::\\w+)?|dot(::\\w+)?|line(::\\w+)?|grid(::\\w+)?)");
				randomNumber = QRegExp("(random\\[[-+]?[0-9]*\\.?[0-9]+,[-+]?[0-9]*\\.?[0-9]+\\])"); // random[-2.3,3.4]

				expression.setCaseSensitivity(Qt::CaseInsensitive);
				primitives.setCaseSensitivity(Qt::CaseInsensitive);
				randomNumber.setCaseSensitivity(Qt::CaseInsensitive);
			};

			void highlightBlock(const QString &text)
			{

				if (currentBlockState() == 2) {
					setFormat(0, text.length(), warningFormat);
					setCurrentBlockState(-1);
					return;
				}


				if (previousBlockState() != 1 && currentBlockState() == 1) {
					// This line was previously a multi-line start 
					if (!text.contains("*/")) setCurrentBlockState(0);
				}

				if (previousBlockState() == 1) {
					// Part of multi-line comment. Skip the rest...
					if (!text.contains("*/")) {
						setFormat(0, text.length(), commentFormat);
						setCurrentBlockState(1);
						return;
					}
				}

				// Line parsing
				QString current;
				int startMatch = 0;
				for (int i = 0; i < text.length(); i++) {
					if ((i > 0) && text.at(i) == '*' && text.at(i-1) == '/') {
						// Multi-line comment begins
						setFormat(i-1, text.length()-i+1, commentFormat);
						setCurrentBlockState(1);
						return;
					}

					if ((i > 0) && text.at(i) == '/' && text.at(i-1) == '*') {
						// Multi-line comment ends
						setFormat(0, i, commentFormat);
						if (currentBlockState() != 0) {
							setCurrentBlockState(0);
						}
						continue;
					}

					if (text.at(0) == '#') {
						// Preprocessor format
						setFormat(0, text.length(), preprocessorFormat);
						continue;
					}

					if ((i > 0) && (i < text.length()-2) && text.at(i) == '/' && text.at(i-1) == '/') {
						// Single-line comments
						setFormat(i-1, text.length()-i+1, commentFormat);
						break;
					}

					bool delimiter = (text.at(i) == '{' || text.at(i) == '\t' || text.at(i) == '}' || text.at(i) == ' '  || (text.at(i) == '\r') || (text.at(i) == '\n'));
					bool lastChar = (i==text.length()-1);
					if (delimiter || lastChar) {
						if (lastChar && !delimiter) current += text.at(i);
						int adder = (i==text.length()-1 ? 1 : 0);
						if (expression.exactMatch(current)) setFormat(startMatch, i-startMatch+adder, keywordFormat);
						if (primitives.exactMatch(current)) setFormat(startMatch, i-startMatch+adder, primitiveFormat);
						if (randomNumber.exactMatch(current)) setFormat(startMatch, i-startMatch+adder, preprocessorFormat);
						if (text.at(i) == '{' || text.at(i) == '}') setFormat(i, 1, bracketFormat);
						startMatch = i;
						current = "";
					} else {
						current += text.at(i);
					}
				}

			}; 
		private:
			QTextCharFormat keywordFormat;
			QTextCharFormat bracketFormat;
			QTextCharFormat primitiveFormat;
			QTextCharFormat commentFormat;
			QTextCharFormat warningFormat;
			QTextCharFormat preprocessorFormat;

			QRegExp expression;
			QRegExp primitives;
			QRegExp randomNumber;
		};


		MainWindow::MainWindow()
		{
			init();
			loadFile(QDir(EXAMPLEDIR).absoluteFilePath("Default.es"));
			tabChanged(0); // to update title.
		}

		MainWindow::MainWindow(const QString &fileName)
		{
			QDir::setCurrent(QCoreApplication::applicationDirPath()); // Otherwise we cannot find examples + templates
			init();
			loadFile(fileName);
			tabChanged(0); // to update title.
		}

		MainWindow::~MainWindow()
		{

		}

		void MainWindow::closeEvent(QCloseEvent *ev)
		{
			bool modification = false;
			for (int i = 0; i < tabInfo.size(); i++)
			{
				if (tabInfo[i].unsaved)
					modification = true;
			}

			if (modification)
			{
				int i = QMessageBox::warning(this, "Unsaved changed", "There are tabs with unsaved changes.\r\nContinue and loose changes?", QMessageBox::Ok, QMessageBox::Cancel);
				if (i == QMessageBox::Ok)
				{
					// OK
					ev->accept();
					return;
				} else {
					// Cancel
					ev->ignore();
					return;
				}
			}
			ev->accept();

			writeSettings();
		}

		void MainWindow::newFile()
		{
			insertTabPage("");
		}

		void MainWindow::open()
		{
			QString filter = "EisenScript (*.es);;All Files (*.*)";
			QString fileName = QFileDialog::getOpenFileName(this, QString(), QString(), filter);
			if (!fileName.isEmpty())
			{
				loadFile(fileName);
			}
		}

		void MainWindow::keyReleaseEvent(QKeyEvent* event)
		{
			bool fullscreen_check = m_fullscreen_action->isChecked();
			if (event->key() == Qt::Key_Escape)
			{
				toggleFullScreen();
			} else if (event->key() == Qt::Key_F5 && fullscreen_check)
			{
				render();
			} else if (event->key() == Qt::Key_F6 && fullscreen_check)
			{
				templateExport();
			} else
			{
				event->ignore();
			}
		};

		bool MainWindow::save()
		{
			int index = m_tab_bar->currentIndex();
			if (index == -1)
			{
				WARNING("No open tab");
				return false;
			} 
			TabInfo t = tabInfo[index];

			if (t.hasBeenSavedOnce)
			{
				return saveFile(t.filename);
			} else
			{
				return saveAs();
			}
		}

		bool MainWindow::saveAs()
		{
			int index = m_tab_bar->currentIndex();
			if (index == -1)
			{
				WARNING("No open tab");
				return false;
			} 

			TabInfo t = tabInfo[index];

			QString filter = "EisenScript (*.es);;All Files (*.*)";

			QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), t.filename, filter);
			if (fileName.isEmpty())
				return false;

			return saveFile(fileName);
		}

		void MainWindow::about()
		{
			QString about_file = MISCDIR + QDir::separator() + "about.html";
			QFile file(about_file);
			if (!file.open(QFile::ReadOnly | QFile::Text))
			{
				WARNING("Could not open about.html...");
				return;
			}

			QTextStream in(&file);
			QString text = in.readAll();

			text.replace("$VERSION$", VERSION.toLongString());

			QMessageBox message_box(this);
			message_box.setText(text);
			message_box.setWindowTitle("About Structure Synth");
			message_box.setIconPixmap(MISCDIR + QDir::separator() + "icon.jpg");
			message_box.setMinimumWidth(800);
			message_box.exec();
		}

		void MainWindow::documentWasModified()
		{
			tabInfo[m_tab_bar->currentIndex()].unsaved = true;
			tabChanged(m_tab_bar->currentIndex());
		}

		void MainWindow::init()
		{
			setAcceptDrops(true);
			setFocusPolicy(Qt::StrongFocus);
			setAttribute(Qt::WA_DeleteOnClose);
			setMouseTracking(true);

			QSplitter*	splitter = new QSplitter(this);
			splitter->setObjectName(QString::fromUtf8("splitter"));
			splitter->setOrientation(Qt::Horizontal);
			m_stacked_text_edits = new QStackedWidget(splitter);
			engine = new SyntopiaCore::GLEngine::EngineWidget(this, splitter);

			m_tab_bar = new QTabBar(this);
			m_tab_bar->setTabsClosable(true);
			connect(m_tab_bar, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
			connect(m_tab_bar, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

			QFrame* frame = new QFrame(this);
			m_frame_layout = new QVBoxLayout();
			m_frame_layout->setSpacing(0);
			m_frame_layout->setMargin(4);
			frame->setLayout(m_frame_layout);
			frame->layout()->addWidget(m_tab_bar);
			frame->layout()->addWidget(splitter);
			setCentralWidget(frame);

			QList<int> l; l.append(100); l.append(400);
			splitter->setSizes(l);

			// Log widget (in dockable window)
			m_log_dock = new QDockWidget(this);
			m_log_dock->setWindowTitle("Log");
			m_log_dock->setObjectName(QString::fromUtf8("logdockwidget"));
			m_log_dock->setAllowedAreas(Qt::BottomDockWidgetArea);
			QWidget* log_dock_content = new QWidget(m_log_dock);
			log_dock_content->setObjectName(QString::fromUtf8("logdockcontent"));
			QVBoxLayout* log_dock_content_layout = new QVBoxLayout(log_dock_content);
			log_dock_content_layout->setObjectName(QString::fromUtf8("log_dock_content_layout"));
			log_dock_content_layout->setContentsMargins(0, 0, 0, 0);

			ListWidgetLogger* logger = new ListWidgetLogger(m_log_dock);
			log_dock_content_layout->addWidget(logger);
			m_log_dock->setWidget(log_dock_content);
			addDockWidget(Qt::BottomDockWidgetArea, m_log_dock);

			// Variable editor (in dockable window)
			m_editor_dock = new QDockWidget(this);
			m_editor_dock->setMinimumWidth(250);
			m_editor_dock->setWindowTitle("Variables");
			m_editor_dock->setObjectName(QString::fromUtf8("editordock"));
			m_editor_dock->setAllowedAreas(Qt::RightDockWidgetArea);
			QWidget* editor_dock_contents = new QWidget(m_editor_dock);
			editor_dock_contents->setObjectName(QString::fromUtf8("editor_dock_contents"));
			QVBoxLayout* editor_dock_contents_layout = new QVBoxLayout(editor_dock_contents);
			editor_dock_contents_layout->setObjectName(QString::fromUtf8("editor_dock_contents_layout"));
			editor_dock_contents_layout->setContentsMargins(0, 0, 0, 0);

			variableEditor = new VariableEditor(m_editor_dock);
			variableEditor->setMinimumWidth(250);
			editor_dock_contents_layout->addWidget(variableEditor);
			m_editor_dock->setWidget(editor_dock_contents);
			addDockWidget(Qt::RightDockWidgetArea, m_editor_dock);
			m_editor_dock->setHidden(true);

			INFO(QString("Welcome to Structure Synth version %1. A Syntopia Project.").arg(VERSION.toLongString()));
			INFO("");
			INFO("Zoom by pressing both mouse buttons, holding SHIFT+left mouse button, or using scroll wheel. Translate using right mouse button. Hold 'ALT' for fast rotate (quick draw mode).");
			INFO("Press 'Reset View' if you get lost in the 3D view.");
			INFO("Use the context menu in the text edit area to get a list of common commands.");
			INFO("");
			INFO("Please report bugs and feature requests at the SourceForge forums (weblink at the Help Menu). Enjoy.");
			//WARNING("This is an experimental SVN checkout build. For stability use the package releases.");

			oldDirtyPosition = -1;
			probeDepth = false;

			createActions();
			createOpenGLContextMenu();

			readSettings();
			createToolBars();
			createStatusBar();
			createMenus();
		}

		void MainWindow::createOpenGLContextMenu()
		{
			QMenu* opengL_context_menu = new QMenu();			
			opengL_context_menu->addAction(m_insert_camera_settings_action);

			m_probe_depth_action = new QAction(tr("Show 3D Object Information"), this);
			m_probe_depth_action->setCheckable(true);
			connect(m_probe_depth_action, SIGNAL(triggered()), this, SLOT(toggleProbeDepth()));
			opengL_context_menu->addAction(m_probe_depth_action);

			opengL_context_menu->addAction(m_fullscreen_action);
			opengL_context_menu->addAction(m_screenshot_action);
			opengL_context_menu->addAction(m_reset_view_action);
			engine->setContextMenu(opengL_context_menu);
		}


		void MainWindow::toggleFullScreen()
		{
			bool fullscreen_check = m_fullscreen_action->isChecked();
			if (fullscreen_check)
			{
				m_frame_layout->setMargin(0);
				m_tab_bar->hide();
				m_stacked_text_edits->hide();
				m_log_dock->hide();
				menuBar()->hide();
				statusBar()->hide();
				m_file_toolbar->hide();
				m_edit_toolbar->hide();
				m_render_toolbar->hide();
				m_random_toolbar->hide();
				showFullScreen();
			} else 
			{
				m_frame_layout->setMargin(4);
				showNormal();
				m_stacked_text_edits->show();
				m_log_dock->show();
				menuBar()->show();
				statusBar()->show();
				m_file_toolbar->show();
				m_edit_toolbar->show();
				m_render_toolbar->show();
				m_tab_bar->show();
				m_random_toolbar->show();
			}
		}


		void MainWindow::toggleProbeDepth()
		{
			getEngine()->toggleShowDepth();
		}

		void MainWindow::createActions()
		{
			m_fullscreen_action = new QAction(tr("F&ullscreen"), this);
			m_fullscreen_action->setShortcut(tr("Ctrl+F"));
			m_fullscreen_action->setCheckable(true);
			m_fullscreen_action->setChecked(false);
			connect(m_fullscreen_action, SIGNAL(triggered()), this, SLOT(toggleFullScreen()));

			m_fast_rotate_action = new QAction(tr("Fast Rotate"), this);
			m_fast_rotate_action->setCheckable(true);
			connect(m_fast_rotate_action, SIGNAL(triggered()), this, SLOT(fastRotateChanged()));

			m_show_coordinate_system_action = new QAction(tr("Show Coordinate System"), this);
			m_show_coordinate_system_action->setCheckable(true);
			connect(m_show_coordinate_system_action, SIGNAL(triggered()), this, SLOT(showCoordinateSystemChanged()));


			m_insert_camera_settings_action = new QAction(tr("&Copy Camera Settings to EisenScript Window"), this);
			connect(m_insert_camera_settings_action, SIGNAL(triggered()), this, SLOT(insertCameraSettings()));

			m_raytrace_final_action = new QAction(tr("&Raytrace (Final)"), this);
			connect(m_raytrace_final_action, SIGNAL(triggered()), this, SLOT(raytrace()));

			m_raytrace_progressive_action = new QAction(tr("&Raytrace (in Window)"), this);
			connect(m_raytrace_progressive_action, SIGNAL(triggered()), this, SLOT(raytraceProgressive()));

			m_new_action = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
			m_new_action->setShortcut(tr("Ctrl+N"));
			m_new_action->setStatusTip(tr("Create a new file"));
			connect(m_new_action, SIGNAL(triggered()), this, SLOT(newFile()));

			m_open_action = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
			m_open_action->setShortcut(tr("Ctrl+O"));
			m_open_action->setStatusTip(tr("Open an existing file"));
			connect(m_open_action, SIGNAL(triggered()), this, SLOT(open()));

			m_save_action = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
			m_save_action->setShortcut(tr("Ctrl+S"));
			m_save_action->setStatusTip(tr("Save the script to disk"));
			connect(m_save_action, SIGNAL(triggered()), this, SLOT(save()));

			m_save_as_action = new QAction(QIcon(":/images/filesaveas.png"), tr("Save &As..."), this);
			m_save_as_action->setStatusTip(tr("Save the script under a new name"));
			connect(m_save_as_action, SIGNAL(triggered()), this, SLOT(saveAs()));

			m_close_action = new QAction(QIcon(":/images/fileclose.png"), tr("&Close Tab"), this);
			m_close_action->setShortcut(tr("Ctrl+W"));
			m_close_action->setStatusTip(tr("Close this tab"));
			connect(m_close_action, SIGNAL(triggered()), this, SLOT(closeTab()));

			m_exit_action = new QAction(QIcon(":/images/exit.png"), tr("E&xit Application"), this);
			m_exit_action->setShortcut(tr("Ctrl+Q"));
			m_exit_action->setStatusTip(tr("Exit the application"));
			connect(m_exit_action, SIGNAL(triggered()), this, SLOT(close()));

			m_cut_action = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
			m_cut_action->setShortcut(tr("Ctrl+X"));
			m_cut_action->setStatusTip(tr("Cut the current selection's contents to the "
				"clipboard"));
			connect(m_cut_action, SIGNAL(triggered()), this, SLOT(cut()));

			m_copy_action = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
			m_copy_action->setShortcut(tr("Ctrl+C"));
			m_copy_action->setStatusTip(tr("Copy the current selection's contents to the "
				"clipboard"));
			connect(m_copy_action, SIGNAL(triggered()), this, SLOT(copy()));

			m_paste_action = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
			m_paste_action->setShortcut(tr("Ctrl+V"));
			m_paste_action->setStatusTip(tr("Paste the clipboard's contents into the current "
				"selection"));
			connect(m_paste_action, SIGNAL(triggered()), this, SLOT(paste()));

			m_render_action = new QAction(QIcon(":/images/render.png"), tr("&Build System"), this);
			m_render_action->setShortcut(tr("F5"));
			m_render_action->setStatusTip(tr("Render the current ruleset"));
			connect(m_render_action, SIGNAL(triggered()), this, SLOT(render()));

			m_export_action = new QAction(tr("&Template Export..."), this);
			m_export_action->setShortcut(tr("F6"));
			m_export_action->setStatusTip(tr("Export the structure using a template."));
			connect(m_export_action, SIGNAL(triggered()), this, SLOT(templateExport()));

			m_screenshot_action = new QAction(tr("&Save as Bitmap..."), this);
			connect(m_screenshot_action, SIGNAL(triggered()), this, SLOT(makeScreenshot()));

			m_reset_view_action = new QAction("Reset View", this);
			m_reset_view_action->setStatusTip(tr("Resets the viewport"));
			connect(m_reset_view_action, SIGNAL(triggered()), this, SLOT(resetView()));

			m_about_action = new QAction(QIcon(":/images/documentinfo.png"), tr("&About"), this);
			m_about_action->setStatusTip(tr("Show the About box"));
			connect(m_about_action, SIGNAL(triggered()), this, SLOT(about()));

			m_sfhome_action = new QAction(QIcon(":/images/agt_internet.png"), tr("&Project Homepage (web link)"), this);
			m_sfhome_action->setStatusTip(tr("Open the SourceForge project page in a browser."));
			connect(m_sfhome_action, SIGNAL(triggered()), this, SLOT(launchSfHome()));

			m_reference_action = new QAction(QIcon(":/images/agt_internet.png"), tr("&Structure Synth Reference (web link)"), this);
			m_reference_action->setStatusTip(tr("Open a Structure Synth reference web page in a browser."));
			connect(m_reference_action, SIGNAL(triggered()), this, SLOT(launchReferenceHome()));

			m_gallery_action = new QAction(QIcon(":/images/agt_internet.png"), tr("&Flickr Structure Synth Group (web link)"), this);
			m_gallery_action->setStatusTip(tr("Opens the main Flickr group for Structure Synth creations."));
			connect(m_gallery_action, SIGNAL(triggered()), this, SLOT(launchGallery()));

			for (int i = 0; i < MaxRecentFiles; ++i)
			{
				QAction* action = new QAction(this);
				action->setVisible(false);
				connect(action, SIGNAL(triggered()), this, SLOT(openFile()));
				m_recentfile_actions.append(action);
			}

			qApp->setWindowIcon(QIcon(":/images/structuresynth.png"));
		}

		void MainWindow::createMenus()
		{
			// -- File Menu --
			m_file_menu = menuBar()->addMenu(tr("&File"));
			m_file_menu->addAction(m_new_action);
			m_file_menu->addAction(m_open_action);
			m_file_menu->addAction(m_save_action);
			m_file_menu->addAction(m_save_as_action);

			for (int i = 0; i < MaxRecentFiles; ++i)
				m_file_menu->addAction(m_recentfile_actions[i]);

			m_file_menu->addSeparator();
			m_file_menu->addAction(m_close_action);
			m_file_menu->addAction(m_exit_action);

			// -- Edit Menu --
			m_edit_menu = menuBar()->addMenu(tr("&Edit"));
			m_edit_menu->addAction(m_cut_action);
			m_edit_menu->addAction(m_copy_action);
			m_edit_menu->addAction(m_paste_action);
			m_edit_menu->addSeparator();
			m_edit_menu->addAction(m_insert_camera_settings_action);
			QMenu* command_menu = m_edit_menu->addMenu("Insert Command");
			createCommandHelpMenu(command_menu, this);

			// -- Render Menu --
			QMenu* render_menu = menuBar()->addMenu(tr("&Render"));
			render_menu->addAction(m_render_action);
			render_menu->addSeparator();
			render_menu->addAction(m_raytrace_progressive_action);
			render_menu->addAction(m_raytrace_final_action);
			render_menu->addSeparator();
			render_menu->addAction(m_fullscreen_action);
			render_menu->addAction(m_reset_view_action);
			render_menu->addSeparator();
			
			render_menu->addAction(m_fast_rotate_action);
			render_menu->addAction(m_show_coordinate_system_action);
			render_menu->addAction(m_probe_depth_action);
			
			// -- Export --
			QMenu* export_menu = menuBar()->addMenu(tr("&Export"));
			export_menu->addAction(m_export_action);
			export_menu->addAction("Obj Export...", this, SLOT(exportToObj()));
			export_menu->addAction(m_screenshot_action);
			//menuBar()->addSeparator();

			// -- Examples Menu --
			QStringList filters;
			QMenu* examples_menu = menuBar()->addMenu(tr("&Examples"));
			// Scan examples dir...
			QDir dir(EXAMPLEDIR);
			filters.clear();
			filters << "*.es";
			dir.setNameFilters(filters);
			if (!dir.exists())
			{
				QAction* a = new QAction("Unable to locate: "+dir.absolutePath(), this);
				a->setEnabled(false);
				examples_menu->addAction(a);
			} else
			{
				// we will recurse the dirs...
				QStack<QString> path_stack;
				path_stack.append(QDir(EXAMPLEDIR).absolutePath());

				QMap< QString , QMenu* > menu_map;
				while (!path_stack.isEmpty())
				{
					QMenu* current_menu = examples_menu;
					QString path = path_stack.pop();
					if (menu_map.contains(path))
						current_menu = menu_map[path];

					QDir current_dir(path);
					QStringList file_lists = current_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
					for (int i = 0; i < (int)file_lists.size(); i++)
					{
						QMenu* menu = new QMenu(file_lists[i]);
						QString absPath = QDir(path + QDir::separator() + file_lists[i]).absolutePath();
						menu_map[absPath] = menu;
						current_menu->addMenu(menu);
						menu->setIcon(QIcon(":/images/folder.png"));
						path_stack.push(absPath);
					}

					current_dir.setNameFilters(filters);

					file_lists = current_dir.entryList();
					for (int i = 0; i < (int)file_lists.size(); i++)
					{
						QAction* action = new QAction(file_lists[i], this);
						action->setIcon(QIcon(":/images/mail_new.png"));
						QString absPath = QDir(path ).absoluteFilePath(file_lists[i]);
						action->setData(absPath);
						connect(action, SIGNAL(triggered()), this, SLOT(openFile()));
						current_menu->addAction(action);
					}
				}
			}

			QMenu* window_menu = createPopupMenu();
			window_menu->setTitle("Windows");
			menuBar()->addMenu(window_menu);

			m_help_menu = menuBar()->addMenu(tr("&Help"));
			m_help_menu->addAction(m_about_action);
			m_help_menu->addSeparator();
			m_help_menu->addAction(m_sfhome_action);
			m_help_menu->addAction(m_reference_action);
			m_help_menu->addAction(m_gallery_action);
		}

		void MainWindow::createToolBars()
		{
			m_file_toolbar = addToolBar(tr("File Toolbar"));
			m_file_toolbar->addAction(m_new_action);
			m_file_toolbar->addAction(m_open_action);
			m_file_toolbar->addAction(m_save_action);

			m_edit_toolbar = addToolBar(tr("Edit Toolbar"));
			m_edit_toolbar->addAction(m_cut_action);
			m_edit_toolbar->addAction(m_copy_action);
			m_edit_toolbar->addAction(m_paste_action);

			m_random_toolbar = addToolBar(tr("Random Toolbar"));

			QLabel* randomSeed = new QLabel("Seed:"); 
			m_random_toolbar->addWidget(randomSeed);
			m_seed_spinbox = new QSpinBox();
			m_seed_spinbox->setRange(1,32768);
			m_seed_spinbox->setValue(1);
			m_random_toolbar->addWidget(m_seed_spinbox);
			m_autoincrement_checkbox = new QCheckBox("Auto Increment", m_random_toolbar);
			m_random_toolbar->addWidget(m_autoincrement_checkbox);
			m_autoincrement_checkbox->setChecked(true);

			m_render_toolbar = addToolBar(tr("Render Toolbar"));
			m_render_toolbar->addAction(m_render_action);
			m_render_toolbar->addWidget(new QLabel("Build    ", this));
			QPushButton* reset_view_button = new QPushButton(this);
			reset_view_button->setText("Reset View");
			m_render_toolbar->addWidget(reset_view_button);
			connect(reset_view_button, SIGNAL(clicked()), this, SLOT(resetView()));
			
			m_progress_box = new SyntopiaCore::GLEngine::ProgressBox(this);
			m_render_toolbar->addWidget(m_progress_box);
			connect(m_progress_box, SIGNAL(startPressed()), this, SLOT(raytraceProgressive()));
			m_progress_box->setValue(0);
			connect(m_seed_spinbox, SIGNAL(valueChanged(int)), this, SLOT(seedChanged()));
		}

		void MainWindow::fastRotateChanged()
		{
			engine->setFastRotate(m_fast_rotate_action->isChecked());
		}

		void MainWindow::showCoordinateSystemChanged()
		{
			engine->setShowCoordinateSystem(m_show_coordinate_system_action->isChecked());
			if (m_show_coordinate_system_action->isChecked())
			{
				INFO("X,Y,Z axis is colored red,green, and blue respectively. Axis length is 10 units.");
			}
			engine->requireRedraw();
		}

		void MainWindow::disableAllExcept(QWidget* w)
		{
			m_disabled_widgets.clear();
			m_disabled_widgets = findChildren<QWidget *>("");
			while (w) 
			{
				m_disabled_widgets.removeAll(w);
				w = w->parentWidget();
			}
			foreach (QWidget* w, m_disabled_widgets)
				w->setEnabled(false);
			qApp->processEvents();
		}

		void MainWindow::enableAll()
		{
			foreach (QWidget* w, m_disabled_widgets)
				w->setEnabled(true);
		}

		void MainWindow::disableExceptProgressBox()
		{

		}
		
		void MainWindow::raytraceProgressive()
		{
			disableAllExcept(m_progress_box);
			RayTracer rt(engine, m_progress_box, true);
			QImage im = rt.calculateImage(engine->width(),engine->height());
			engine->setImage(im);
			enableAll();
		}

		void MainWindow::seedChanged() 
		{
			m_autoincrement_checkbox->setChecked(false);
		}

		void MainWindow::createStatusBar()
		{
			statusBar()->showMessage(tr("Ready"));
		}

		void MainWindow::readSettings()
		{
			QSettings settings("Syntopia Software", "Structure Synth");
			QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
			QSize size = settings.value("size", QSize(1024, 800)).toSize();
			move(pos);
			resize(size);
		}

		void MainWindow::writeSettings()
		{
			QSettings settings;
			settings.setValue("pos", pos());
			settings.setValue("size", size());
		}

		void MainWindow::openFile()
		{
			QAction *action = qobject_cast<QAction *>(sender());
			if (action)
			{
				loadFile(action->data().toString());
			} else
			{
				WARNING("No data!");
			}
		}

		void MainWindow::loadFile(const QString &fileName)
		{
			insertTabPage(fileName);
		}

		bool MainWindow::saveFile(const QString &fileName)
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return false;
			}

			QFile file(fileName);
			if (!file.open(QFile::WriteOnly | QFile::Text))
			{
				QMessageBox::warning(this, tr("Structure Synth"),
					tr("Cannot write file %1:\n%2.")
					.arg(fileName)
					.arg(file.errorString()));
				return false;
			}

			QTextStream out(&file);
			QApplication::setOverrideCursor(Qt::WaitCursor);
			out << getTextEdit()->toPlainText();
			QApplication::restoreOverrideCursor();

			tabInfo[m_tab_bar->currentIndex()].hasBeenSavedOnce = true;
			tabInfo[m_tab_bar->currentIndex()].unsaved = false;
			tabInfo[m_tab_bar->currentIndex()].filename = fileName;
			tabChanged(m_tab_bar->currentIndex()); // to update displayed name;

			statusBar()->showMessage(tr("File saved"), 2000);
			setRecentFile(fileName);
			return true;
		}

		QString MainWindow::strippedName(const QString &fullFileName)
		{
			return QFileInfo(fullFileName).fileName();
		}

		void MainWindow::updateRandom()
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return;
			}

			m_seed_spinbox->blockSignals(true);
			setSeed((getSeed()+1) % 32768);
			m_seed_spinbox->blockSignals(false);
			INFO(QString("Auto-incremented random seed: %1").arg(getSeed()));

			// Should we try something like below?
			if (tabInfo[m_tab_bar->currentIndex()].unsaved) {
				// Current tab is unsaved, we will not change the random seed.
			} else {
				// We will auto-increment random seed.
			}

			RandomStreams::SetSeed(getSeed());
		}

		void MainWindow::render()
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return;
			}

			if (getTextEdit()->toPlainText().startsWith("#javascript", Qt::CaseInsensitive))
			{
				// This is javascript...
				QString text = getTextEdit()->toPlainText();
				text = text.remove("#javascript", Qt::CaseInsensitive);

				TabInfo t = tabInfo[m_tab_bar->currentIndex()];
				QString dir;
				if (t.hasBeenSavedOnce)
				{
					dir = QFileInfo(t.filename).absolutePath();
				} else {
					dir = ""; // we will use the default dir.
				}

				parseJavaScript(text,dir);
				return;
			}

			setEnabled(false);
			if (m_autoincrement_checkbox->isChecked())
				updateRandom();
			
			RandomStreams::SetSeed(getSeed());
			INFO(QString("Random seed: %1").arg(getSeed()));

			engine->setDisabled(true);

			try 
			{
				Rendering::OpenGLRenderer renderTarget(engine);
				renderTarget.begin(); // we clear before parsing...

				Preprocessor preprocessor;
				QString out = preprocessor.Process(getTextEdit()->toPlainText(), getSeed());
				bool showGUI = false;
				out = variableEditor->updateFromPreprocessor(&preprocessor, out, &showGUI);
				m_editor_dock->setHidden(!showGUI);

				Tokenizer tokenizer(out);
				EisenParser e(&tokenizer);
				INFO("Started Eisenstein engine...");
				RuleSet* rs = e.parseRuleset();

				rs->resolveNames();

				rs->dumpInfo();

				Builder b(&renderTarget, rs, true);
				b.build();
				renderTarget.end();

				//INFO("Done...");

				if (b.seedChanged()) {
					setSeed(b.getNewSeed());
					INFO(QString("Builder changed seed to: %1").arg(b.getNewSeed()));
				} 

				if (oldDirtyPosition > 0) {
					getTextEdit()->document()->markContentsDirty(oldDirtyPosition,1);
					oldDirtyPosition = -1;
				}

				engine->setRaytracerCommands(b.getRaytracerCommands());
				INFO(QString("Setting %1 raytracer commands.").arg(b.getRaytracerCommands().count()));

				delete(rs); 
				rs = 0;

			} catch (ParseError& pe)
			{
				WARNING(pe.getMessage());
				int pos = pe.getPosition();
				INFO(QString("Found at character %1.").arg(pos));	
				getTextEdit()->document()->findBlock(pos).setUserState(2);
				getTextEdit()->document()->markContentsDirty(pos,1);
				oldDirtyPosition = pos;
				engine->clearWorld();
				engine->requireRedraw();
			} catch (Exception& er) {
				WARNING(er.getMessage());
				engine->clearWorld();
				engine->requireRedraw();
			} 
			setEnabled(true);

			engine->setDisabled(false);
		}

		void MainWindow::resetView()
		{
			engine->reset();
		}

		QTextEdit* MainWindow::getTextEdit()
		{
			return (m_stacked_text_edits->currentWidget() ?
				(QTextEdit*)m_stacked_text_edits->currentWidget() : nullptr);
		}

		void MainWindow::cursorPositionChanged()
		{
			if (!this->getTextEdit())
				return;

			int pos = this->getTextEdit()->textCursor().position();
			int blockNumber = this->getTextEdit()->textCursor().blockNumber();
			statusBar()->showMessage(QString("Position: %1, Line: %2").arg(pos).arg(blockNumber + 1), 5000);
		}

		void MainWindow::insertTabPage(QString filename)
		{
			QTextEdit* textEdit = new TextEdit();
			connect(textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));

			textEdit->setLineWrapMode(QTextEdit::NoWrap);
			textEdit->setTabStopWidth(20);
			new EisenScriptHighlighter(textEdit);

			QString s = QString("// Write EisenScript code here...\r\n");
			textEdit->setText(s);

			bool loadingSucceded = false;
			if (!filename.isEmpty())
			{
				INFO(QString("Loading file: %1").arg(filename));
				QFile file(filename);
				if (!file.open(QFile::ReadOnly | QFile::Text))
				{
					textEdit->setPlainText(QString("Cannot read file %1:\n%2.").arg(filename).arg(file.errorString()));
				} else
				{
					QTextStream in(&file);
					QApplication::setOverrideCursor(Qt::WaitCursor);
					textEdit->setPlainText(in.readAll());
					QApplication::restoreOverrideCursor();
					statusBar()->showMessage(QString("Loaded file: %1").arg(filename), 2000);
					loadingSucceded = true;
				}
			}

			QString displayName = filename;
			if (displayName.isEmpty())
			{
				// Find a new name
				displayName = "Unnamed";
				QString suggestedName = displayName;

				bool unique = false;
				int counter = 1;
				while (!unique)
				{
					unique = true;
					for (int i = 0; i < tabInfo.size(); i++) {
						if (tabInfo[i].filename == suggestedName) {
							INFO("equal");
							unique = false;
							break;
						}	
					}
					if (!unique) suggestedName = displayName + " " + QString::number(counter++);
				}
				displayName = suggestedName;
			}

			m_stacked_text_edits->addWidget(textEdit);
			if (loadingSucceded) 
			{
				tabInfo.append(TabInfo(displayName, textEdit, false, true));
				setRecentFile(filename);
			} else 
			{
				tabInfo.append(TabInfo(displayName, textEdit, true));
			}

			QString tabTitle = QString("%1%3").arg(strippedName(displayName)).arg(!loadingSucceded? "*" : "");
			m_tab_bar->setCurrentIndex(m_tab_bar->addTab(strippedName(tabTitle)));
			connect(textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
		}

		void MainWindow::tabChanged(int index)
		{
			int size = (int)tabInfo.size();
			if (index >= size || index < 0)
				return;

			TabInfo t = tabInfo[index];
			QString tabTitle = QString("%1%3").arg(strippedName(t.filename)).arg(t.unsaved ? "*" : "");
			setWindowTitle(QString("%1 - %2").arg(tabTitle).arg("Structure Synth"));
			m_stacked_text_edits->setCurrentWidget(t.textEdit);
			m_tab_bar->setTabText(m_tab_bar->currentIndex(), tabTitle);
		}

		void MainWindow::closeTab()
		{
			int index = m_tab_bar->currentIndex();
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return;
			}
			closeTab(index);
		}

		void MainWindow::closeTab(int index)
		{		
			TabInfo t = tabInfo[index];
			if (t.unsaved) {
				int answer = QMessageBox::warning(this, QString("Unsaved changes"), "Close this tab without saving changes?", "OK", "Cancel");
				if (answer == 1)
					return;
			}

			tabInfo.remove(index);
			m_tab_bar->removeTab(index);

			m_stacked_text_edits->removeWidget(t.textEdit);
			delete(t.textEdit); // ?
		}

		void MainWindow::launchSfHome()
		{
			INFO("Launching web browser...");
			bool s = QDesktopServices::openUrl(QUrl("http://structuresynth.sourceforge.net/"));
			if (!s) WARNING("Failed to open browser...");
		}

		void MainWindow::launchReferenceHome()
		{
			INFO("Launching web browser...");
			bool s = QDesktopServices::openUrl(QUrl("http://structuresynth.sourceforge.net/reference.php"));
			if (!s) WARNING("Failed to open browser...");
		}

		void MainWindow::launchGallery()
		{
			INFO("Launching web browser...");
			bool s = QDesktopServices::openUrl(QUrl("http://flickr.com/groups/structuresynth/"));
			if (!s) WARNING("Failed to open browser...");
		}

		void MainWindow::saveImage(QImage image)
		{
			QList<QByteArray> formats = QImageWriter::supportedImageFormats();
			QStringList allowedTypesFilter;
			QStringList allowedTypes;
			for (int i = 0; i < formats.count(); i++)
			{
				allowedTypesFilter.append("*." + formats[i]);
				allowedTypes.append(formats[i]);
			}
			QString filter = "Image Files (" + allowedTypesFilter.join(" ") + ")";

			QString filename = QFileDialog::getSaveFileName(this, "Save Screenshot As...", QString(), filter);
			if (filename.isEmpty())
			{
				INFO("User cancelled save...");
				return;
			}

			QString ext = filename.section(".", -1).toLower();
			if (!allowedTypes.contains(ext))
			{
				WARNING("Invalid image extension.");
				WARNING("File must be one of the following types: " + allowedTypes.join(","));
				return;
			}

			bool succes = image.save(filename);
			if (succes)
			{
				INFO("Saved screenshot as: " + filename);
			} else
			{
				WARNING("Save failed! Filename: " + filename);
			}
		}

		void MainWindow::makeScreenshot()
		{
			QImage image = engine->getScreenShot();
			saveImage(image);
		}

		void MainWindow::setSeed(int randomSeed)
		{
			m_seed_spinbox->setValue(randomSeed);
		}

		int MainWindow::getSeed()
		{
			return m_seed_spinbox->value();
		};

		void MainWindow::insertCameraSettings()
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return;
			}

			getTextEdit()->insertPlainText(engine->getCameraSettings());
			INFO("Camera settings are now pasted into the script window.");
			INFO("Remember to clear previous 'set' commands if necessary.");
		}

		QString MainWindow::getScriptWithSettings(QString filename)
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return "";
			}

			QString s = "// Autogenerated script for file: " + filename + "\n";
			s += "// Generated " + QDateTime::currentDateTime().toString("MMMM dd yyyy hh:mm:ss") + "\n";
			s += QString("// Original window size: %1x%2").arg(engine->width()).arg(engine->height()) + "\n\n";
			s += engine->getCameraSettings() + "\n";
			s += QString("Set seed %1\n\n").arg(getSeed());
			s += QString("// Original script:\n\n");
			s += getTextEdit()->toPlainText();
			return s;
		}

		void MainWindow::templateRenderToFile()
		{
			QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), "output.txt");
			if (fileName.isEmpty()) {
				INFO("User cancelled.");
				return;
			}

			templateRender(fileName);
		}

		void MainWindow::templateRender()
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return;
			}

			templateRender(""); // Renders to clip board when file name is empty.
		}

		void MainWindow::templateRender(const QString& fileName)
		{
			if (m_tab_bar->currentIndex() == -1) { WARNING("No open tab"); return; }

			QAction *action = qobject_cast<QAction *>(sender());
			if (action) {
				QDir d(TEMPLATEDIR);
				QString templateFileName = d.absoluteFilePath(action->data().toString());
				INFO("Starting Template Renderer: " + fileName);
				try {
					Template myTemplate(templateFileName);
					templateRender(fileName, &myTemplate, "");
				} catch (Exception& er) {
					WARNING(er.getMessage());
				}
			} else {
				WARNING("No data!");
			}
		}

		void MainWindow::templateRender(const QString& fileName, Model::Rendering::Template* myTemplate, QString inputText,
			int width, int height, bool postModify)
		{
			RandomStreams::SetSeed(getSeed());
			if (inputText.isEmpty()) inputText = getTextEdit()->toPlainText();
			INFO(QString("Random seed: %1").arg(getSeed()));
			try {
				if (width == 0) width = engine->width();
				if (height == 0) height = engine->height();
				TemplateRenderer rendering(*myTemplate);
				Vector3f cameraRight=  (engine->getCameraPosition()-engine->getCameraTarget()).cross(engine->getCameraUp());
				cameraRight.normalize();
				rendering.setCamera(
					engine->getCameraPosition(), 
					engine->getCameraUp().normalized(), 
					cameraRight,
					engine->getCameraTarget(),
					width, height, width/(double)height, engine->getFOV());

				rendering.setBackgroundColor(engine->getBackgroundColor());
				rendering.begin(); 

				Preprocessor pp;
				QString out = pp.Process(inputText, getSeed());
				bool showGUI = false;
				out = variableEditor->updateFromPreprocessor(&pp, out, &showGUI);
				m_editor_dock->setHidden(!showGUI);

				Tokenizer tokenizer(out);
				EisenParser e(&tokenizer);
				INFO("Started Eisenstein engine...");
				RuleSet* rs = e.parseRuleset();

				rs->resolveNames();

				rs->dumpInfo();

				Builder b(&rendering, rs, true);
				b.build();
				rendering.end();

				if (b.seedChanged()) {
					setSeed(b.getNewSeed());
					INFO(QString("Builder changed seed to: %1").arg(b.getNewSeed()));
				} 

				QString output = rendering.getOutput();

				if (postModify) {
					// Post modify output.
					QDialog* d = new QDialog(this);
					QVBoxLayout* vl = new QVBoxLayout(d);

					d->resize(800,600);
					QTextEdit* te = new QTextEdit(d);
					vl->addWidget(te);
					te->setText(output);

					QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
						| QDialogButtonBox::Cancel);
					vl->addWidget(buttonBox);						

					connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
					connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

					if (d->exec() == QDialog::Accepted) {
						output = te->toPlainText();
					} else {
						WARNING("User cancelled...");
						return;
					}
				}

				if (fileName.isEmpty()){
					QClipboard *clipboard = QApplication::clipboard();
					clipboard->setText(output); 
					INFO("Done...");
					INFO("Script is now copied to the clipboard");
				} else {
					QFile file(fileName);
					INFO("Writing to file: " + QFileInfo(file).absoluteFilePath());
					if (!file.open(QFile::WriteOnly | QFile::Text)) {
						QMessageBox::warning(this, tr("Structure Synth"),
							tr("Cannot write file %1:\n%2.")
							.arg(fileName)
							.arg(file.errorString()));
						return;
					}

					QTextStream out(&file);
					QApplication::setOverrideCursor(Qt::WaitCursor);
					out << output;
					QApplication::restoreOverrideCursor();
					INFO("File saved.");
				}

				delete(rs);
				rs = 0;
			} catch (Exception& er) {
				WARNING(er.getMessage());
			}
		}

		void MainWindow::parseJavaScript(QString scripture, QString dir) {
			JavaScriptParser jsp(this, statusBar());
			jsp.parse(scripture, dir);
		}

		void MainWindow::copy()
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return;
			}
			getTextEdit()->copy();
		}

		void MainWindow::cut()
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return;
			}
			getTextEdit()->cut();
		}

		void MainWindow::paste()
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return;
			}
			getTextEdit()->paste();
		}

		void MainWindow::dragEnterEvent(QDragEnterEvent* event)
		{
			if (event->mimeData()->hasUrls())
			{
				event->acceptProposedAction();
			} else
			{
				INFO("Cannot accept MIME object: " + event->mimeData()->formats().join(" - "));
			}
		}

		void MainWindow::dropEvent(QDropEvent* event)
		{
			if (event->mimeData()->hasUrls())
			{
				QList<QUrl> urls = event->mimeData()->urls();
				for (int i = 0; i < urls.size() ; i++)
				{
					INFO("Loading: " + urls[i].toLocalFile());
					loadFile(urls[i].toLocalFile());
				}
			} else
			{
				INFO("Cannot accept MIME object: " + event->mimeData()->formats().join(" - "));
			}
		}

		void MainWindow::templateExport()
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return;
			}

			// We must parse first...
			RuleSet* rs = 0;
			QStringList primitives;
			try {	
				Preprocessor pp;
				QString out = pp.Process(getTextEdit()->toPlainText(), getSeed());
				bool showGUI = false;
				out = variableEditor->updateFromPreprocessor(&pp, out, &showGUI);
				m_editor_dock->setHidden(!showGUI);

				Tokenizer tokenizer(out);
				EisenParser e(&tokenizer);
				INFO("Checking EisenScript...");
				rs = e.parseRuleset();
				primitives = rs->resolveNames();

				rs->dumpInfo();
			} catch (Exception& er) {
				WARNING("Could not export, because script could not be parsed:");
				WARNING(er.getMessage());
				return; // something went wrong...
			}

			TemplateExportDialog dialog(this, primitives);
			dialog.setDefaultSize(engine->width(), engine->height());
			dialog.setTemplatePath(TEMPLATEDIR);
			dialog.exec();
		}

		void MainWindow::setRecentFile(const QString &fileName)
		{
			QSettings settings;
			QStringList files = settings.value("recentFileList").toStringList();
			files.removeAll(fileName);
			files.prepend(fileName);
			while (files.size() > MaxRecentFiles)
				files.removeLast();

			settings.setValue("recentFileList", files);
			int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

			for (int i = 0; i < numRecentFiles; ++i)
			{
				QString text = tr("&%1 %2").arg(i + 1).arg(QFileInfo(files[i]).fileName());
				m_recentfile_actions[i]->setText(text);
				QString abs_path = QFileInfo(files[i]).absoluteFilePath();
				m_recentfile_actions[i]->setData(abs_path);
				m_recentfile_actions[i]->setVisible(true);
			}

			for (int j = numRecentFiles; j <  MaxRecentFiles; ++j)
				m_recentfile_actions[j]->setVisible(false);
		}

		void MainWindow::raytrace()
		{
			INFO("Hint: use the 'set raytracer::size [0x800]' command to set the dimensions. use 'set raytracer::samples 10' to control quality."); 
			disableAllExcept(m_progress_box);
			RayTracer rt(engine, m_progress_box, false);
			QImage im = rt.calculateImage(0,0);
			enableAll();
			PreviewWindow pd(this, im);
			pd.exec();
		}

		PreviewWindow::PreviewWindow(MainWindow* mainWindow, QImage im) : QDialog(mainWindow), mainWindow(mainWindow), image(im) {
			QVBoxLayout *layout = new QVBoxLayout(this);
			setLayout(layout);

			QHBoxLayout* hlayout = new QHBoxLayout();

			QPushButton* pb = new QPushButton(this);
			pb->setText("Save as Bitmap...");
			connect(pb, SIGNAL(clicked()), this, SLOT(saveImage()));
			hlayout->addWidget(pb);

			QPushButton* pb2 = new QPushButton(this);
			pb2->setText("Close");
			connect(pb2, SIGNAL(clicked()), this, SLOT(close()));
			hlayout->addWidget(pb2);

			hlayout->addStretch(10);
			layout->addLayout(hlayout);

			QLabel* lb = new QLabel(this);
			lb->setPixmap(QPixmap::fromImage(image));
			lb->resize(im.width(), im.height());
			layout->addWidget(lb);
			resize(lb->size());
		};

		void PreviewWindow::saveImage() {
			mainWindow->saveImage(image);
		}

		namespace {
			class ObjDialog : public QDialog {
			public:
				ObjDialog(QWidget* parent) : QDialog(parent) {
					QSettings s;

					setWindowTitle("Obj Export Settings");
					QVBoxLayout* vl = new QVBoxLayout(this);
					
					groupByTaggingCheckBox = new QCheckBox("Group by Tagging", this);
					vl->addWidget(groupByTaggingCheckBox);
					bool groupByTagging = s.value("ObjDialog/groupByTagging", true).toBool();
					groupByTaggingCheckBox->setChecked(groupByTagging);
					
					groupByColorCheckBox = new QCheckBox("Group by Color", this);
					bool groupByColor = s.value("ObjDialog/groupByColor", false).toBool();
					groupByColorCheckBox->setChecked(groupByColor);
					vl->addWidget(groupByColorCheckBox);
					
					QHBoxLayout* hl = new QHBoxLayout(this);
					
					QLabel* l = new QLabel(QString("Sphere resolution: Latitude: "), this);
					spinBox1 = new QSpinBox(this);
					spinBox1->setMinimum(2);
					spinBox1->setMaximum(40);
					int latResolution = s.value("ObjDialog/latResolution", 10).toInt();
					spinBox1->setValue(latResolution);
					QLabel* l2 = new QLabel(QString(" divs, Longitude: "), this);
					spinBox2 = new QSpinBox(this);
					spinBox2->setMinimum(2);
					spinBox2->setMaximum(40);
					int longResolution = s.value("ObjDialog/longResolution", 10).toInt();					
					spinBox2->setValue(longResolution);
					QLabel* l3 = new QLabel(QString(" divs."));
					hl->addWidget(l);
					hl->addWidget(spinBox1);
					hl->addWidget(l2);
					hl->addWidget(spinBox2);
					hl->addWidget(l3);
					vl->addLayout(hl);

					QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
					vl->addWidget(buttonBox);						

					connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
					connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

					vl->addWidget(buttonBox);
				};

				~ObjDialog() {
					QSettings s;
					s.setValue("ObjDialog/groupByTagging", groupByTaggingCheckBox->isChecked());
					s.setValue("ObjDialog/groupByColor", groupByColorCheckBox->isChecked());
					s.setValue("ObjDialog/latResolution", spinBox1->value());
					s.setValue("ObjDialog/longResolution", spinBox2->value());
				}
				
				QSpinBox* spinBox1;
				QSpinBox* spinBox2;
				QCheckBox* groupByTaggingCheckBox;
				QCheckBox* groupByColorCheckBox ;

			};
		}

		void MainWindow::insertText()
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return;
			}

			QString text = ((QAction*)sender())->text();
			getTextEdit()->insertPlainText(text.section("//",0,0)); // strip comments
		}

		void MainWindow::exportToObj()
		{
			if (m_tab_bar->currentIndex() == -1)
			{
				WARNING("No open tab");
				return;
			}

			ObjDialog obj_dialog(this);
			if (obj_dialog.exec() == QDialog::Rejected)
				return;

			int dt = obj_dialog.spinBox1->value();
			int dp = obj_dialog.spinBox2->value();

			QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), "output.obj");
			if (fileName.isEmpty())
			{
				INFO("User cancelled.");
				return;
			}

			RandomStreams::SetSeed(getSeed());
			QString inputText = getTextEdit()->toPlainText();

			INFO(QString("Random seed: %1").arg(getSeed()));
			try {
				ObjRenderer renderer(dt,dp, obj_dialog.groupByTaggingCheckBox->isChecked(), obj_dialog.groupByColorCheckBox->isChecked() );
				renderer.begin(); 

				Preprocessor pp;
				QString out = pp.Process(inputText, getSeed());
				bool showGUI = false;
				out = variableEditor->updateFromPreprocessor(&pp, out, &showGUI);
				m_editor_dock->setHidden(!showGUI);

				Tokenizer tokenizer(out);
				EisenParser e(&tokenizer);
				INFO("Started Eisenstein engine...");
				RuleSet* rs = e.parseRuleset();
				rs->resolveNames();
				rs->dumpInfo();

				Builder b(&renderer, rs, true);
				b.build();
				renderer.end();


				QFile file(fileName);
				INFO("Writing to file: " + QFileInfo(file).absoluteFilePath());
				if (!file.open(QFile::WriteOnly | QFile::Text))
				{
					QMessageBox::warning(this, tr("Structure Synth"),
						tr("Cannot write file %1:\n%2.")
						.arg(fileName)
						.arg(file.errorString()));
					return;
				}

				QTextStream out2(&file);
				QApplication::setOverrideCursor(Qt::WaitCursor);
				renderer.writeToStream(out2);
				QApplication::restoreOverrideCursor();
				INFO("File saved.");
				delete(rs);
			} catch (Exception& er)
			{
				WARNING(er.getMessage());
			}
		}
	}
}

