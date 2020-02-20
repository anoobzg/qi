#pragma once

#include <QMainWindow>
#include <QTabBar>
#include <QStackedWidget>
#include <QTextEdit>
#include <QCheckBox>

#include "../../SyntopiaCore/GLEngine/EngineWidget.h"
#include "../../SyntopiaCore/Misc/Version.h"
#include "VariableEditor.h"
#include "../Model/Rendering/TemplateRenderer.h"
#include "../Model/Builder.h"



class QAction;
class QMenu;
class QTextEdit;

namespace StructureSynth {
	namespace GUI {
 
		struct TabInfo {
			TabInfo() {}; 
			TabInfo(QString filename, QTextEdit* textEdit) : filename(filename), unsaved(false), textEdit(textEdit), hasBeenSavedOnce(false) {};
			TabInfo(QString filename, QTextEdit* textEdit, bool unsaved, bool hasBeenSavedOnce=false) : filename(filename), unsaved(unsaved), textEdit(textEdit), hasBeenSavedOnce(hasBeenSavedOnce) {};
			QString filename;
			bool unsaved;
			QTextEdit* textEdit;
			bool hasBeenSavedOnce;			
        };

		
		// A modified QTextEdit with an extended context menu
		class TextEdit : public QTextEdit {
			Q_OBJECT
			public:
				TextEdit() : QTextEdit() {};
				TextEdit(QWidget* parent) : QTextEdit(parent) {};

				void contextMenuEvent(QContextMenuEvent *event);
			public slots:
				void insertText();
		};
		
		/// The main window of the application.
		class MainWindow : public QMainWindow
		{
			Q_OBJECT
		public:
			MainWindow();
			MainWindow(const QString &fileName);
			virtual ~MainWindow();

			void setSeed(int randomSeed);
			int getSeed();
			void templateRender(const QString& fileName, Model::Rendering::Template* myTemplate, QString inputText, int width = 0, int height = 0, bool postModify = false);

			SyntopiaCore::GLEngine::EngineWidget* getEngine() { return engine; };
			void saveImage(QImage im);
			
			QString getScriptWithSettings(QString filename);
			
			SyntopiaCore::GLEngine::ProgressBox* getProgressBox() { return m_progress_box; };

			void disableAllExcept(QWidget* widget);
			void enableAll();
			void disableExceptProgressBox();
		protected:
			void dragEnterEvent(QDragEnterEvent* event);
			void dropEvent(QDropEvent* event);
			void closeEvent(QCloseEvent* event);
			void keyReleaseEvent(QKeyEvent* event);

		private slots:
			void templateExport();
			void toggleProbeDepth();
			void seedChanged();
			void raytraceProgressive();
			void templateRender();
			void templateRenderToFile();
			void templateRender(const QString& fileName);		
			void raytrace();
			void documentWasModified();
			void render();
			void resetView();

			void exportToObj();
			void makeScreenshot();

			void newFile();
			void open();
			bool save();
			bool saveAs();

			void cut();
			void copy();
			void paste();
			void insertCameraSettings();
			void insertText();

			void showCoordinateSystemChanged();
			void fastRotateChanged();
			void toggleFullScreen();
			void cursorPositionChanged();

			void about();
			void launchSfHome();
			void launchGallery();
			void launchReferenceHome();

			void openFile();
			void tabChanged(int index);
			void closeTab();
			void closeTab(int index);
		private:
			void insertTabPage(QString filename);
			void loadFile(const QString &fileName);
			bool saveFile(const QString &fileName);
		private:
			void parseJavaScript(QString scripture, QString dir);

			void setRecentFile(const QString& fileName);
			QTextEdit* getTextEdit();  //获取当前的QTextEdit
		protected:
			void init();
			void createActions();
			void createMenus();
			void createToolBars();
			void createStatusBar();

			void readSettings();
			void writeSettings();
		protected:
			void updateRandom();
			QString strippedName(const QString &fullFileName);
			void createOpenGLContextMenu();

			SyntopiaCore::GLEngine::EngineWidget* engine;

			QVector<TabInfo> tabInfo;

			int oldDirtyPosition;
			bool probeDepth;
			
			SyntopiaCore::GLEngine::ProgressBox* m_progress_box;
			QSpinBox* m_seed_spinbox;
			QCheckBox* m_autoincrement_checkbox;
			///////////Menu
			QMenu *m_file_menu;
			QMenu *m_edit_menu;
			QMenu *m_help_menu;

			///////////Toolbar
			QToolBar *m_file_toolbar;
			QToolBar *m_render_toolbar;
			QToolBar *m_edit_toolbar;
			QToolBar *m_random_toolbar;

			///////////actions
			QAction* m_fullscreen_action;
			QAction *m_new_action;
			QAction *m_open_action;
			QAction *m_save_action;
			QAction *m_save_as_action;
			QAction *m_close_action;
			QAction* m_exit_action;

			QVector<QAction*> m_recentfile_actions;

			QAction* m_cut_action;
			QAction* m_copy_action;
			QAction* m_paste_action;
			QAction* m_insert_camera_settings_action;

			QAction* m_render_action;
			QAction* m_reset_view_action;

			QAction* m_probe_depth_action;
			QAction* m_fast_rotate_action;
			QAction* m_show_coordinate_system_action;
			QAction* m_raytrace_final_action;
			QAction* m_raytrace_progressive_action;

			QAction* m_export_action;
			QAction* m_screenshot_action;

			QAction* m_about_action;
			QAction* m_sfhome_action;
			QAction* m_reference_action;
			QAction* m_gallery_action;
			///////////
			QVBoxLayout* m_frame_layout;

			QTabBar* m_tab_bar;

			QStackedWidget* m_stacked_text_edits;

			QDockWidget* m_log_dock;
			VariableEditor* variableEditor;
			QDockWidget* m_editor_dock;

			///////////
			QList<QWidget*> m_disabled_widgets;
		};

		class PreviewWindow : public QDialog {
			Q_OBJECT
		public:
			PreviewWindow(MainWindow* parent, QImage im) ;
		public slots:
			void saveImage();
		private: 
			MainWindow* mainWindow;
			QImage image;
		};

	}
}

