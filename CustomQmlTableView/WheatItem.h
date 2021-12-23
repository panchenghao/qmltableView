#ifndef WHEATITEM_H
#define WHEATITEM_H
#include <memory>
#include <QObject>
#include <QMetaType>
class WheatItemPrivate;
class WheatItem: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sampleid READ sampleid WRITE setSampleid NOTIFY sampleidChanged)
    Q_PROPERTY(QString createTime READ createTime WRITE setCreateTime NOTIFY createTimeChanged)
    Q_PROPERTY(QString checked READ checked WRITE setChecked NOTIFY checkedChanged)
    Q_ENUMS(DelegateType)
public:
    QString sampleid();
    void setSampleid(QString value);

    QString createTime();
    void setCreateTime(QString value);

    QString checked();
    void setChecked(QString value);
signals:
    void sampleidChanged();
    void createTimeChanged();
    void checkedChanged();
public:
    explicit WheatItem(QObject* parent=nullptr);
    explicit WheatItem(QStringList dataList,QObject* parent=nullptr);

    WheatItem(const WheatItem& item);

    WheatItem(WheatItem&& item);
    WheatItem& operator=(WheatItem&& item);
    WheatItem& operator=(const WheatItem& item);
    ~WheatItem();
public:
    enum DelegateType {TextEditor,CheckboxEditor};
    DelegateType delegateType();
    void setDelegateType(DelegateType value);
    QString indexData(int index);
private:
    std::shared_ptr<WheatItemPrivate> m_wheatItemPrivate;
    DelegateType m_delegateType;
};
Q_DECLARE_METATYPE(WheatItem)
#endif // WHEATITEM_H
