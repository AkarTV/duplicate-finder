#include "comparison_binary.h"
#include "QDirIterator"

unsigned Comparison_binary::counter = 0;
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
        QFile file(it.next());
        if(file.open(QIODevice::ReadOnly)){
            list_of_files.insert(file.size(), file.fileName());
        }
    }
}

QStringList Comparison_binary::get_equals() const
{
    QStringList list_of_equals;
    QMultiHash<QByteArray, QString> hash_list_of_files;
    for(auto key_ : list_of_files.uniqueKeys())
    {
        int count = list_of_files.count(key_);
        if(count > 1)
        {
            QStringList files_with_equal_size;
            QMultiHash<qint64, QString>::ConstIterator i = list_of_files.find(key_);
            for( ; i != list_of_files.constEnd() && i.key() == key_; ++i)
            {
                files_with_equal_size.append(i.value());
            }
            for(int i = 0; i < count-1; ++i)
            {
                QString temporary_list;
                QFile file1(files_with_equal_size.at(i));
                file1.open(QIODevice::ReadOnly);
                bool flag_for_first_file = false;
                for(int j = i+1; j <count; ++j)
                {
                    bool flag_for_second_file = true;
                    QFile file2(files_with_equal_size.at(j));
                    file2.open(QIODevice::ReadOnly);
                    while(!file1.atEnd() && !file2.atEnd())
                    {
                            if(file1.readLine() != file2.readLine())
                            {
                                flag_for_second_file = false;
                                break;
                            }
                    }
                    if(flag_for_second_file)
                    {
                        temporary_list.append(file2.fileName() + '\n');
                        ++counter;
                        files_with_equal_size.removeAt(j);
                        --count;
                        --j;
                        flag_for_first_file = true;
                    }
                    file2.close();
                    file1.reset();
                }
                if(flag_for_first_file)
                {
                    temporary_list.append(file1.fileName());
                    ++counter;
                    files_with_equal_size.removeAt(i);
                    --count;
                    --i;
                    list_of_equals.append(temporary_list);
                }
            }
        }
    }
    return list_of_equals;
}

unsigned Comparison_binary::get_total_counter() const
{
    return counter;
}

Comparison_binary::~Comparison_binary()
{
    counter = 0;
}
