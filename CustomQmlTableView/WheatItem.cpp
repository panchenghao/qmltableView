#include "WheatItem.h"
class WheatItemPrivate{
    public:
    QString m_sampleId {""};
    QString m_createTime {""};
    QString m_checked {"false"};
};

QString WheatItem::sampleid()
{
    return m_wheatItemPrivate->m_sampleId;
}

void WheatItem::setSampleid(QString value)
{
    m_wheatItemPrivate->m_sampleId=value;
    emit sampleidChanged();
}

QString WheatItem::createTime()
{
    return m_wheatItemPrivate->m_createTime;
}

void WheatItem::setCreateTime(QString value)
{
    m_wheatItemPrivate->m_createTime=value;
    emit createTimeChanged();
}

QString WheatItem::checked()
{
    return m_wheatItemPrivate->m_checked;
}

void WheatItem::setChecked(QString value)
{
    m_wheatItemPrivate->m_checked=value;
    emit checkedChanged();
}

WheatItem::WheatItem(QObject* parent):QObject(parent),
    m_wheatItemPrivate(std::make_shared<WheatItemPrivate>())
{

}

WheatItem::WheatItem(QStringList dataList, QObject *parent):QObject(parent),
    m_wheatItemPrivate(std::make_shared<WheatItemPrivate>())
{
    setSampleid(dataList.at(0));
    setCreateTime(dataList.at(1));
    setDelegateType(TextEditor);
}

WheatItem::WheatItem(const WheatItem &item)
{
    m_wheatItemPrivate=item.m_wheatItemPrivate;
    m_delegateType=item.m_delegateType;
}

WheatItem::WheatItem(WheatItem &&item)
{
    m_wheatItemPrivate=item.m_wheatItemPrivate;
    m_delegateType=item.m_delegateType;
}

WheatItem &WheatItem::operator=(WheatItem &&item)
{
    m_wheatItemPrivate=item.m_wheatItemPrivate;
    m_delegateType=item.m_delegateType;
    return *this;
}

WheatItem &WheatItem::operator=(const WheatItem &item)
{
    m_wheatItemPrivate=item.m_wheatItemPrivate;
    m_delegateType=item.m_delegateType;
    return *this;
}

WheatItem::~WheatItem()
{

}

WheatItem::DelegateType WheatItem::delegateType()
{
    return m_delegateType;
}

void WheatItem::setDelegateType(DelegateType value)
{
    m_delegateType=value;
}

QString WheatItem::indexData(int index)
{
    QString value="";
    switch (index) {
    case 0:value=m_wheatItemPrivate->m_checked;
        break;
    case 1:value=m_wheatItemPrivate->m_sampleId;
        break;
    case 2:value=m_wheatItemPrivate->m_createTime;
        break;
    default:break;
    }
    return value;
}
