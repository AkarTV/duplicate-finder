#ifndef COMPARISON_BINARY_H
#define COMPARISON_BINARY_H
#include "QDir"
#include "QByteArray"
#include "QMultiHash"

class Comparison_binary
{
public:
    Comparison_binary(const QDir& dir1, const QDir& dir2);
    QStringList get_equals() const;
private:
    QMultiHash<QByteArray, QString> binary_list_of_files;
    void add_to_list(const QDir& directory);
};

#endif // COMPARISON_BINARY_H
