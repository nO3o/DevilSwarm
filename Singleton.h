#pragma once

#define DECLARE_SINGLETON(Type)             \
public:                                     \
    static Type* GetInstance();            \
    static void DestroyInstance();         \
public:                                     \
    Type(const Type&) = delete;             \
    Type& operator=(const Type&) = delete;  \
private:                                    \
    static Type* m_pInstance;               

#define IMPLEMENT_SINGLETON(Type)           \
Type* Type::m_pInstance = nullptr;          \
Type* Type::GetInstance() {                \
    if (nullptr == m_pInstance)             \
        m_pInstance = new Type;             \
    return m_pInstance;                     \
}                                           \
void Type::DestroyInstance() {             \
    if (m_pInstance) {                      \
        m_pInstance->Release();             \
        if(m_pInstance) {                   \
        delete m_pInstance;                 \
        m_pInstance = nullptr;              \
        }                                   \
    }                                       \
}      

