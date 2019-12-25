#include "IDisk.h"

namespace DB
{
DiskDirectoryIterator::DiskDirectoryIterator(std::unique_ptr<IDiskDirectoryIteratorImpl> && impl_) : impl(std::move(impl_))
{
}

bool DiskDirectoryIterator::operator==(DiskDirectoryIterator const & other) const
{
    if (other.impl)
        return impl == other.impl;
    else
        return !impl->isValid();
}

bool DiskDirectoryIterator::operator!=(DiskDirectoryIterator const & other) const
{
    if (other.impl)
        return impl != other.impl;
    else
        return impl->isValid();
}

DiskDirectoryIterator & DiskDirectoryIterator::operator++()
{
    impl->next();
    return *this;
}

String DiskDirectoryIterator::operator*() const
{
    return impl->name();
}


bool IDisk::isDirectoryEmpty(const String & path)
{
    return iterateDirectory(path) == DiskDirectoryIterator();
}
}
