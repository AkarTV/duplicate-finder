#include "comparison_binary.h"
#include "QMessageBox"

Comparison_binary::Comparison_binary(const QDir& directory)
{
    QFileInfoList directory_file_list(directory.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries));
    QFileInfoList::ConstIterator i = directory_file_list.constBegin();
    while(i != directory_file_list.constEnd())
    {
        QFile file(i->absoluteFilePath());
        if(file.open(QIODevice::ReadOnly))
            binary_list_of_files[i->fileName()] = QByteArray(file.readAll());
        ++i;
    }
}

QStringList Comparison_binary::get_equals(const Comparison_binary& second_dir)
{
    QStringList list_of_equals;
    QMap<QString, QByteArray>::ConstIterator i = binary_list_of_files.constBegin();
    while(i != binary_list_of_files.constEnd())
    {
        QMap<QString, QByteArray>::ConstIterator j = second_dir.binary_list_of_files.constBegin();
        while(j != second_dir.binary_list_of_files.constEnd())
        {
            if(i.value() == j.value())
                list_of_equals.append("1 Directory/ " + i.key() + " == " + "2 Directory/ " + j.key());
            ++j;
        }
        ++i;
    }
    return list_of_equals;
}
