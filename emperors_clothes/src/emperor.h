#pragma once

#include <streams.h>
#include "clothes.h"
#include "registry.h"
#include "idle_time.h"

class CEmperorFilter
    : public CTransInPlaceFilter
    , public IIdleTime
    , public ISpecifyPropertyPages {
    Clothes _clothes;
    Registry _registry;
    unsigned int _idleTimeValue;

public:
    static CUnknown * WINAPI CreateInstance(LPUNKNOWN pUnk, HRESULT *phr);

    DECLARE_IUNKNOWN

    CEmperorFilter(LPUNKNOWN pUnk, HRESULT *phr);

    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv);

    HRESULT Transform(IMediaSample *pSample);
    HRESULT CheckInputType(const CMediaType *mtIn);

    STDMETHODIMP Pause();
    STDMETHODIMP Run(REFERENCE_TIME tStart);

    STDMETHODIMP GetPages(CAUUID *pPages);
    STDMETHODIMP GetIdleTime(unsigned int *idleTime) const;
    STDMETHODIMP UpdateIdleTime(unsigned int idleTime);
};
