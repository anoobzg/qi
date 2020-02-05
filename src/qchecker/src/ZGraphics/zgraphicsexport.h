#pragma once
#include <QObject>

#ifdef ZG_EXPORT
#define ZG_API Q_DECL_EXPORT
#else
#define ZG_API Q_DECL_IMPORT
#endif