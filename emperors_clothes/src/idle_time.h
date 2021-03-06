#pragma once

#include <objbase.h>


DECLARE_INTERFACE_(IIdleTime, IUnknown) {
    STDMETHOD(GetIdleTime)(unsigned int *idleTime) const PURE;
    STDMETHOD(UpdateIdleTime)(unsigned int idleTime) PURE;
};