#ifndef ENZYME_GLOBAL_H
#define ENZYME_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ENZYME_LIBRARY)
#  define ENZYMESHARED_EXPORT Q_DECL_EXPORT
#else
#  define ENZYMESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ENZYME_GLOBAL_H
