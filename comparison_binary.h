#ifndef COMPARISON_BINARY_H
#define COMPARISON_BINARY_H
#include "QDir"
#include "QMultiHash"

class Comparison_binary
{
public:
    Comparison_binary(const QDir& dir1, const QDir& dir2);
    QStringList get_equals() const;
    unsigned get_total_counter() const;
    ~Comparison_binary();
private:
    QMultiHash<qint64, QString> list_of_files;
    void add_to_list(const QDir& directory);
    static unsigned total_file_number;
};

#endif // COMPARISON_BINARY_H
