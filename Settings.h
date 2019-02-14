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


/**
 * @class SettingsManager
 * @brief 用于统一管理系统中的各个对象的可配置参数，提供保存，载入等功能
 * 访问其中的设置项采用key的形式进行，key的一般格式为 "前缀名称/属性名称" 例如： "setttingsTest/name" 表示 通用设置->音量
 *      [1]...  SettingsTest
 *      [3]...
 */
class SettingsManager : public Settings
{
    Q_OBJECT
    Q_PROPERTY(SettingsList allSettings READ allSettings WRITE setAllSettings)

public:
    SettingsManager();
    virtual ~SettingsManager();

    /**
     * 从ini文件载入所有的系统设置
     * @return     成功返回true
     */
    virtual bool load(const QString& iniPath) Q_DECL_OVERRIDE;

    /**
     * 保存所有的系统设置到ini文件
     * @return     成功返回true
     */
    virtual bool save(const QString& iniPath) Q_DECL_OVERRIDE;

    /**
     * 重置所有设置为默认值
     */
    virtual void reset() Q_DECL_OVERRIDE;

    /**
     * 根据key获取当前指定项系统设置的值
     * @param[in]  key      键值(例如："printer/xOffset")
     * @return     QVariant 成功返回有效的值
     */
    QVariant value(const QString& key);

    /**
     * 根据key设置当前指定项系统设置的值
     * @param[in]  key      键值(例如："printer/xOffset")
     * @param[in]  value    需要设置的值
     * @return     bool     成功返回true
     */
    bool setValue(const QString& key, const QVariant& value);

    /**
     * getter/setter for m_allSettings
     */
    void setAllSettings(const SettingsList& allSettings)
    {
        foreach (Settings* settings, allSettings)
        {
            addSettings(settings);
        }
    }
    SettingsList allSettings() const
    {
        return m_allSettings;
    }

public:
    void addSettings(Settings* settings);

protected:
    SettingsList m_allSettings;                 //!< 系统的所有设置项的列表
};

class SettingsTest : public Settings
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged RESET resetName)
public:
    explicit SettingsTest()
        : Settings()
        , name("default")
    {

    }

    QString getName() const{return name;}
    void setName(const QString &value)
    {
        if (name != value)
        {
            emit nameChanged();
            name = value;
        }
    }
    void resetName(){name = "name";}
signals:
    void nameChanged();

public slots:

private:
    QString name;
};

#endif // __SETTINGS_H
/*********************************************************************************************************
** End of file
*********************************************************************************************************/
