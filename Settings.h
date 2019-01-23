/*-------------------------------------------------------------------------------
文件名称：Settings.h
文件描述：通过Q_PROPERTY的形式来访问系统设置，允许载入/保存/复位。
        每个需要保存变量的界面包含一个这个对象，再 将这个对象放在一个链表中。
备    注：
作者   ：闫葛
完成日期：2016/09/21
修改日期：每次修改请注明修改内容和日期

---------------------------------------------------------------------------------*/

#ifndef __SETTINGS_H
#define __SETTINGS_H

#include <QObject>
#include <QMetaProperty>

/**
 *  @class Settings
 *  @brief 系统设置
 */
class Settings : public QObject
{
    Q_OBJECT

public:
    Settings();
    virtual ~Settings();

public:
    /** 
     * 从ini文件中载入全部系统设置，并保存到各个Q_PROPERTY
     * @param[in]  iniPath ini文件路径
     * @return     bool    全部载入成功返回true，否则返回false
     */
    virtual bool load(const QString& iniPath);

    /** 
     * 向ini文件中保存各个Q_PROPERTY中记录的全部系统设置
     * @param[in]  iniPath ini文件路径
     * @return     bool    全部保存成功返回true，否则返回false
     */
    virtual bool save(const QString& iniPath);

    /** 
     * 将全部系统设置复位至默认值，相当于“恢复出厂设置”
     */
    virtual void reset();

protected:
    typedef QList<QMetaProperty> PropertyList;

    /** 
     * 获取当前设置对象的全部需要存储/载入的Q_PROPERTY属性
     * @return     PropertyList 属性列表
     * @note       注意Q_PROPERTY有一个STORED参数可以控制该属性是否需要存储
     */
    PropertyList allStoredProperties() const;
};

typedef QList<Settings*> SettingsList;

#endif // __SETTINGS_H
/*********************************************************************************************************
** End of file
*********************************************************************************************************/
