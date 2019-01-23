/*-------------------------------------------------------------------------------
文件名称： includes.h
文件描述： 全局包含文件，为了保持一致性，每个cpp文件必须包含此文件，即使不需要此文件中的内容
备    注：
作者   ：闫葛
完成日期：2015/06/29
修改日期：每次修改请注明修改内容和日期

---------------------------------------------------------------------------------*/

#ifndef __INCLUDES_H
#define __INCLUDES_H
#define DATETIME_FORMATE "yyyy/MM/dd hh:mm:ss"

#include "MainWindow.h"
#define MAINWINDOW MainWindow::instance()

/*
 * @brief 包含公共头文件
 */
#if defined(_DEBUG) || 1
#include <QDebug>
#endif

#include <QDebug>
#define PRINT_ERR (qDebug() \
    <<"file: " << __FILE__ << ";  " \
    << "funcion: " << __FUNCTION__ << ";  " \
    << "line: " << __LINE__ << ";  " \
    );

/**
 *  @brief 此处用于处理VS2010编译器的utf-8编码问题，
 *         必须保证每一个包含中文字符的源码文件均使用此pragma
 */
#if defined(_MSC_VER) && (_MSC_VER >= 1600)  
# pragma execution_character_set("utf-8")  
#endif

/**
 *  @macro Q_ENABLE_COPY
 *  @brief 表示一个QObject的子类可以被拷贝（对应Q_DISABLE_COPY系统宏），仅用于支持元对象系统的对象动态创建
 *  @note  本宏仅需要在基类的头文件中使用一次，推荐使用在Q_OBJECT宏的下方一行，或者其他类似的显著位置
 */
#define Q_ENABLE_COPY(_type)                                                                            \
    public: _type(const _type& other) {                                                                 \
        Q_UNUSED(other);                                                                                \
        Q_ASSERT_X(false, #_type" Meta Copy-Constructor", #_type" Meta-Objects can NOT be copied.");    \
    }                                                                                                   

#if defined(ENABLE_DYNAMIC_LIBRARY) && ENABLE_DYNAMIC_LIBRARY
#ifdef FIELD_TREE_LIBRARY
#define FIELD_TREE_EXPORT                  Q_DECL_EXPORT
#else
#define FIELD_TREE_EXPORT                  Q_DECL_IMPORT
#endif
#else
#define FIELD_TREE_EXPORT
#endif

#endif                                                                  /* __INCLUDES_H                 */
/*********************************************************************************************************
** End of file
*********************************************************************************************************/
