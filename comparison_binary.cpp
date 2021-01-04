#include "comparison_binary.h"
#include "QDirIterator"

unsigned Comparison_binary::total_file_number = 0;
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
    QStringList result_list;
    QMultiHash<QByteArray, QString> hash_list_of_files;
    for(auto key_ : list_of_files.uniqueKeys())
    {
        int count_of_files = list_of_files.count(key_);
        if(count_of_files > 1)
        {
            QStringList equal_files;
            QMultiHash<qint64, QString>::ConstIterator i = list_of_files.find(key_);
            for( ; i != list_of_files.constEnd() && i.key() == key_; ++i)
                equal_files.append(i.value());
            for(int i = 0; i < count_of_files-1; ++i)
            {
                QString temporary_list_of_files;
                QFile file1(equal_files.at(i));
                file1.open(QIODevice::ReadOnly);
                bool equal_to_first_file = false;
                for(int j = i+1; j <count_of_files; ++j)
                {
                    bool second_file_is_equal = true;
                    QFile file2(equal_files.at(j));
                    file2.open(QIODevice::ReadOnly);
                    while(!file1.atEnd() && !file2.atEnd())
                    {
                            if(file1.read(1000) != file2.read(1000))
                            {
                                second_file_is_equal = false;
                                break;
                            }
                    }
                    if(second_file_is_equal)
                    {
                        temporary_list_of_files.append(file2.fileName() + '\n');
                        ++total_file_number;
                        equal_files.removeAt(j);
                        --count_of_files;
                        --j;
                        equal_to_first_file = true;
                    }
                    file2.close();
                    file1.reset();
                }
                if(equal_to_first_file)
                {
                    temporary_list_of_files.append(file1.fileName());
                    ++total_file_number;
                    equal_files.removeAt(i);
                    --count_of_files;
                    --i;
                    result_list.append(temporary_list_of_files);
                }
            }
        }
    }
    return result_list;
}

unsigned Comparison_binary::get_total_counter() const
{
    return total_file_number;
}

Comparison_binary::~Comparison_binary()
{
    total_file_number = 0;
}
