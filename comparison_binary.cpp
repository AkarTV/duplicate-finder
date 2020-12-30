#include "comparison_binary.h"
#include "QMessageBox"
#include "QCryptographicHash"
#include "QDirIterator"

Comparison_binary::Comparison_binary(const QDir& dir1, const QDir& dir2)
{
    add_to_list(dir1);
    add_to_list(dir2);
}

void Comparison_binary::add_to_list(const QDir& directory)
{
    QDirIterator it(directory, QDirIterator::Subdirectories);
    while(it.hasNext())
    {
        QCryptographicHash hash(QCryptographicHash::Md5);
        QFile file(it.next());
        if(file.open(QIODevice::ReadOnly))
        {
            hash.addData(file.readAll());
            binary_list_of_files.insert(hash.result(), file.fileName());
        }
    }
}

QStringList Comparison_binary::get_equals() const
{
    QStringList list_of_equals;
    for(auto key_ : binary_list_of_files.uniqueKeys())
    {
        if(binary_list_of_files.count(key_) > 1)
        {
            QString equal_files;
            QMultiHash<QByteArray, QString>::ConstIterator i = binary_list_of_files.find(key_);
            for( ; i != binary_list_of_files.end() && i.key() == key_; ++i)
                equal_files.append(i.value() + " | ");
            list_of_equals.append(equal_files);
        }
    }
    return list_of_equals;
}
