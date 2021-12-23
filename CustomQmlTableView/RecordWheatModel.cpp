#include "RecordWheatModel.h"
#include <QDebug>
QVariantList RecordWheatModel::headRoles()
{
    return m_headRoles;
}

void RecordWheatModel::setHeadRoles(QVariantList value)
{
    m_headRoles=value;
    emit headRolesChanged();
}

int RecordWheatModel::rows()
{
    return m_rows;
}

void RecordWheatModel::setRows(int value)
{
    m_rows=value;
    emit rowsChanged();
}

RecordWheatModel::RecordWheatModel(QObject* parent):
    RecordBaseModel<WheatItem>(parent)
{
    setHeadRoles({"打印选择","样本号","检测时间"});
//    mDatas.append(WheatItem({"1","2021-21-22 12:00:12"}));
//    mDatas.append(WheatItem({"2","2021-21-22 13:00:12"}));
//    mDatas.append(WheatItem({"3","2021-21-22 14:00:12"}));
//    mDatas.append(WheatItem({"4","2021-21-22 12:00:12"}));
//    mDatas.append(WheatItem({"5","2021-21-22 13:00:12"}));
//    mDatas.append(WheatItem({"6","2021-21-22 14:00:12"}));
//    mDatas.append(WheatItem({"7","2021-21-22 12:00:12"}));
//    mDatas.append(WheatItem({"8","2021-21-22 13:00:12"}));
//    mDatas.append(WheatItem({"9","2021-21-22 14:00:12"}));
//    mDatas.append(WheatItem({"10","2021-21-22 12:00:12"}));
//    mDatas.append(WheatItem({"11","2021-21-22 13:00:12"}));
//    mDatas.append(WheatItem({"12","2021-21-22 14:00:12"}));
//    mDatas.append(WheatItem({"13","2021-21-22 12:00:12"}));
//    mDatas.append(WheatItem({"14","2021-21-22 13:00:12"}));
//    mDatas.append(WheatItem({"15","2021-21-22 14:00:12"}));
//    mDatas.append(WheatItem({"16","2021-21-22 12:00:12"}));
//    mDatas.append(WheatItem({"17","2021-21-22 13:00:12"}));
//    mDatas.append(WheatItem({"18","2021-21-22 14:00:12"}));
//    mDatas.append(WheatItem({"19","2021-21-22 12:00:12"}));
//    mDatas.append(WheatItem({"20","2021-21-22 13:00:12"}));
//    mDatas.append(WheatItem({"21","2021-21-22 14:00:12"}));
    QVector<QStringList> data;
    for(int i=0;i<100;i++){
        data.append(QStringList()<<QString::number(i)<<QString::number(i));
    }
    initModel(data);
    qDebug()<<"init finsh";
}

QHash<int, QByteArray> RecordWheatModel::roleNames() const
{
    return {
        {CellDataRole,"cellData"},
        {CellTypeRole,"cellType"}
    };
}

int RecordWheatModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_headRoles.size();
}

QVariant RecordWheatModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (!index.isValid() || !indexInRange(index)) return result;
    WheatItem item(std::move(mDatas.at(index.row())));
    bool isNameColumn (index.column() == 0);
    switch (role) {
        case CellDataRole: result = item.indexData(index.column());
            break;
        case CellTypeRole: result = isNameColumn ? WheatItem::CheckboxEditor : item.delegateType();
            break;
//        case CellFlagsRole:     result = isNameColumn  ?  Property::ReadOnly : property->flags();
//            break;
//        case CellEditorRole:    result = isNameColumn  ?  Property::TextEditor : property->editorType();
//            break;
//        case CellOptionRole:    result = isNameColumn  ?  QVariant() : property->option();
//            break;
        default:
            break;
    }
    //qDebug()<<result;
    return result;

}

QVariant RecordWheatModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal)   result=m_headRoles.at(section);
        //if (orientation == Qt::Vertical)     result=m_columnNames.at(section);
    }
    return result;
}

bool RecordWheatModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || !indexInRange(index)) return false;
    switch (role) {
        case CellDataRole:
            if (index.column()== 0){
                if(m_oldtItem&&m_oldIndex!=index)
                {
                    m_oldtItem->setChecked("false");
                    if(m_oldIndex.isValid()) emit dataChanged(m_oldIndex,m_oldIndex,{role});
                }
                 m_oldIndex=index;
                 mDatas[index.row()].setChecked(value.toString());
                 m_currentItem=&mDatas[index.row()];
                 m_oldtItem=m_currentItem;
            }
            break;
        default:
            return false;
    }
    emit dataChanged(index,index,{role});
    return true;
}

Qt::ItemFlags RecordWheatModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEditable;
}

bool RecordWheatModel::canFetchMore(const QModelIndex &parent) const
{
    //if (parent.isValid())
        return false;
   // return (m_itemCount < mDatas.size());
}

void RecordWheatModel::fetchMore(const QModelIndex &parent)
{
    if (parent.isValid())
        return;
    int remainder = mDatas.size() - m_itemCount;
    int itemsToFetch = qMin(500, remainder);

    if (itemsToFetch <= 0)
        return;
    beginInsertRows(QModelIndex(), m_itemCount, m_itemCount + itemsToFetch - 1);
    m_itemCount += itemsToFetch;
    endInsertRows();
    //emit rowsChanged();
    setRows(rowCount());
}


void RecordWheatModel::initModel(QVector<QStringList> value)
{
    beginResetModel();
    for(auto& it:value){
        mDatas.append(WheatItem(it));
    }
    m_currentItem=nullptr;
    m_oldtItem=nullptr;
    m_oldIndex=QModelIndex();
    endResetModel();
    setRows(rowCount());
    //fetchMore({});
}

void RecordWheatModel::selectData()
{
    if(m_currentItem&&m_currentItem->checked()=="true"){
        qDebug()<<m_currentItem->createTime();
    }else{
        qDebug()<<"wei xuan zhong";
    }
    //fetchMore({});
}

void RecordWheatModel::updateData()
{
    //fetchMore({});
}

bool RecordWheatModel::indexInRange(const QModelIndex &index) const
{
   return index.row()>=0 && index.row()< rowCount() && index.column()>=0 && index.column()<columnCount();
}
