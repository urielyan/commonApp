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
        return false;

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

/*********************************************************************************************************
** End of file
*********************************************************************************************************/
