#include "includes.h"
#include "Settings.h"

#include <QSettings>
#include <QMetaObject>
#include <QMetaProperty>

Settings::Settings()
    : QObject()
{

}

Settings::~Settings()
{

}

bool Settings::load(const QString& iniPath)
{
    QSettings iniFile(iniPath, QSettings::IniFormat);
    if (iniFile.status() != QSettings::NoError)
        return false;

    bool ok = true;
    PropertyList storedProperties = allStoredProperties();
    for (PropertyList::const_iterator property = storedProperties.cbegin();
         property != storedProperties.cend();
         ++property)
    {
        QVariant loadedValue = iniFile.value(this->objectName()+"/"+property->name());
        if (!loadedValue.isValid())
        {
            ok = false;
        }
        else if (!property->write(this, loadedValue))
        {
            ok = false;
        }
    }

    return ok;
}

bool Settings::save(const QString& iniPath)
{
    QSettings iniFile(iniPath, QSettings::IniFormat);
    if (iniFile.status() != QSettings::NoError)
    {
        return false;
    }

    bool ok = true;
    PropertyList storedProperties = allStoredProperties();
    for (PropertyList::const_iterator property = storedProperties.cbegin();
         property != storedProperties.cend();
         ++property)
    {
        QVariant propertyValue = property->read(this);
        if (!propertyValue.isValid())
        {
            ok = false;
        }
        iniFile.setValue(this->objectName()+"/"+property->name(), propertyValue);
    }
    iniFile.sync();
    return ok;
}

void Settings::reset()
{
    PropertyList storedProperties = allStoredProperties();
    for (PropertyList::const_iterator property = storedProperties.cbegin();
         property != storedProperties.cend();
         ++property)
    {
        property->reset(this);
    }
}

/** 
 * 获取当前设置对象的全部需要存储/载入的Q_PROPERTY属性
 * @return     PropertyList 属性列表
 * @note       注意Q_PROPERTY有一个STORED参数可以控制该属性是否需要存储
 */
Settings::PropertyList Settings::allStoredProperties() const
{
    PropertyList properties;

    const QMetaObject* metaObject = this->metaObject();
    if (metaObject)
    {
        int numOfProperties = metaObject->propertyCount();
        // 首个属性永远是QObject基类的objectName，此属性不需要保存，直接跳过
        for (int i = 1; i < numOfProperties; ++i)
        {
            QMetaProperty property = metaObject->property(i);
            if (property.isStored())
            {
                properties.push_back(property);
            }
        }
    }

    return properties;
}



//用于定义SettingsManager
SettingsManager::SettingsManager()
    : Settings()
{
    Settings* settings = NULL;
    qDebug() << m_allSettings.size() << __LINE__;
    settings = new SettingsTest();
    settings->setObjectName("test");
    addSettings(settings);
    qDebug() << m_allSettings.size() << __LINE__;
}

SettingsManager::~SettingsManager()
{
}

/**
 * 重置所有设置为默认值
 */
void SettingsManager::reset()
{
    foreach (Settings* settings, m_allSettings)
    {
        settings->reset();
    }
}

/**
 * 从ini文件载入所有的系统设置
 * @return     成功返回true
 */
bool SettingsManager::load(const QString& iniPath)
{
    bool ok = true;

    foreach (Settings* settings, m_allSettings)
    {
        if (!settings->load(iniPath))
        {
            ok = false;
        }
    }

    return ok;
}

/**
 * 保存所有的系统设置到ini文件
 * @return     成功返回true
 */
bool SettingsManager::save(const QString& iniPath)
{
    bool ok = true;

    foreach (Settings* settings, m_allSettings)
    {
        if (!settings->save(iniPath))
        {
            ok = false;
        }
    }

    return ok;
}

/**
 * 根据key获取当前指定项系统设置的值
 * @param[in]  key      键值(例如："printer/xOffset")
 * @return     QVariant 成功返回有效的值
 */
QVariant SettingsManager::value(const QString& key)
{
    QStringList keys = key.split('/');
    if (keys.count() == 2)
    {
        const QString& settingsName = keys[0];
        const QString& propertyName = keys[1];
        foreach (Settings* settings, m_allSettings)
        {
            if (settings->objectName() == settingsName)
            {
                return settings->property(propertyName.toLatin1());
            }
        }
    }
    return QVariant();
}

/**
 * 根据key设置当前指定项系统设置的值
 * @param[in]  key      键值(例如："printer/xOffset")
 * @param[in]  value    需要设置的值
 * @return     bool     成功返回true
 */
bool SettingsManager::setValue(const QString& key, const QVariant& value)
{
    QStringList keys = key.split('/');
    if (keys.count() == 2)
    {
        const QString& settingsName = keys[0];
        const QString& propertyName = keys[1];
        foreach (Settings* settings, m_allSettings)
        {
            if (settings->objectName() == settingsName)
            {
                return settings->setProperty(propertyName.toLatin1(), value);
            }
        }
    }
    return false;
}

void SettingsManager::addSettings(Settings* settings)
{
    if (settings)
    {
        settings->setParent(this);
        m_allSettings.append(settings);
    }
}


/*********************************************************************************************************
** End of file
*********************************************************************************************************/
