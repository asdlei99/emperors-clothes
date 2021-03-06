#include "clothes.h"
#include "constants.h"


POINT lastCursorPos = {};
DWORD lastCursorTime = 0;

inline void ShowCursor() {
    while (ShowCursor(TRUE) < 0);
}

inline void HideCursor() {
    while (ShowCursor(FALSE) >= 0);
}

void CALLBACK CheckLastInput(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    POINT curCursorPos;
    if (GetCursorPos(&curCursorPos) == FALSE) {
        return;
    }

    if (curCursorPos.x != lastCursorPos.x || curCursorPos.y != lastCursorPos.y) {
        lastCursorPos = curCursorPos;
        lastCursorTime = dwTime;
    }
    DWORD idleTime = dwTime - lastCursorTime;

    Clothes *_clothes = reinterpret_cast<Clothes *>(GetProp(hwnd, CLOTHES_WINDOW_PROP_NAME));
    if (idleTime > _clothes->GetIdleTimeValue()) {
        HideCursor();
    } else if (idleTime <= TIMER_INTERVAL) {
        ShowCursor();
    }
}

Clothes::Clothes(const IIdleTime *idleTime)
    : _hClothesWindow(nullptr)
    , _idleTime(idleTime) {
}

unsigned int Clothes::GetIdleTimeValue() const {
    unsigned int _idleTimeValue;
    HRESULT hr = _idleTime->GetIdleTime(&_idleTimeValue);

    if (SUCCEEDED(hr)) {
        return _idleTimeValue;
    } else {
        return IDLE_TIME_DEFAULT;
    }
}

void Clothes::Pause() {
    if (_hClothesWindow != nullptr) {
        ShowCursor();
        RemoveProp(_hClothesWindow, CLOTHES_WINDOW_PROP_NAME);
        KillTimer(_hClothesWindow, TIMER_ID);
    }
}

void Clothes::Run() {
    _hClothesWindow = GetForegroundWindow();
    if (_hClothesWindow == nullptr) {
        return;
    }

    // check existing attribute to avoid conflict
    if (GetProp(_hClothesWindow, CLOTHES_WINDOW_PROP_NAME) == nullptr) {
        SetProp(_hClothesWindow, CLOTHES_WINDOW_PROP_NAME, this);
        SetTimer(_hClothesWindow, TIMER_ID, TIMER_INTERVAL, CheckLastInput);
    }
}