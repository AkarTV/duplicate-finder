#ifndef COMPARISON_BINARY_H
#define COMPARISON_BINARY_H
#include "QDir"
#include "QByteArray"
#include "QMap"

class Comparison_binary
{
public:
    Comparison_binary(QDir& directory);
    QStringList get_equals(const Comparison_binary&);
private:
    QMap<QString, QByteArray> binary_list_of_files;
};

#endif // COMPARISON_BINARY_H
