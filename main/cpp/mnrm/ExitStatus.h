#pragma once

/**
 * \file booltype.h
 */

#include <cstring>
#include <string>

#define BOOL_T_LEN 2048

/**
 * Type to return true/false with error description.
 *
 * This type is intended to be used as a return value of functions, which
 * return true on success and false on failure. Additionally, when an error
 * is returned, an error description can be set. The error description can
 * be retrieved using the bool_t::getErrorString member function.
 *
 * To make it easier to use, you can just return an error description, in
 * which case the boolean value of the type will automatically be 'false'.
 */
class ExitStatus
{
public:
        //// Just set true or false, but leave the error description undefined in case of 'false'.
        explicit ExitStatus(bool f = true);

        /// Set the return value to 'false', and the error string to the specified value.
        explicit ExitStatus(const char* pStr);

        /// Set the return value to 'false', and the error string to the specified value.
        explicit ExitStatus(const std::string& err);

        /// Copy constructor.
        ExitStatus(const ExitStatus& b);

        /// Assignment operator.
        ExitStatus& operator=(const ExitStatus& b);

        /// Returns a description of the error.
        std::string getErrorString() const;

        /// Returns true or false, depending on the contents of this object.
        operator bool() const;

        bool success() const;

private:
        ///
        void strncpy(const char* pSrc);

        ///
        void setErrorString(const std::string& err);

        ///
        void setErrorString(const char* pStr);

private:
        char        m_errorString[BOOL_T_LEN];
        static char s_defaultErrMsg[];
        static char s_defaultSuccessMsg[];
};

inline ExitStatus::ExitStatus(bool f)
{
        if (f)
                m_errorString[0] = 0;
        else
                setErrorString(s_defaultErrMsg);
}

inline ExitStatus::ExitStatus(const char* pStr) { setErrorString(pStr); }

inline ExitStatus::ExitStatus(const std::string& err) { setErrorString(err); }

inline void ExitStatus::strncpy(const char* pSrc)
{
        ::strncpy(m_errorString, pSrc, BOOL_T_LEN);
        m_errorString[BOOL_T_LEN - 1] = 0;
}

inline ExitStatus::ExitStatus(const ExitStatus& b)
{
        if (b.m_errorString[0] == 0) // No error
                m_errorString[0] = 0;
        else
                strncpy(b.m_errorString);
}

inline void ExitStatus::setErrorString(const std::string& s) { setErrorString(s.c_str()); }

inline void ExitStatus::setErrorString(const char* pStr)
{
        if (pStr == 0 || pStr[0] == 0)
                strncpy(s_defaultErrMsg);
        else
                strncpy(pStr);
}

inline ExitStatus& ExitStatus::operator=(const ExitStatus& b)
{
        if (b.m_errorString[0] == 0) // No error
                m_errorString[0] = 0;
        else
                strncpy(b.m_errorString);

        return *this;
}

inline std::string ExitStatus::getErrorString() const
{
        if (m_errorString[0] == 0)
                return s_defaultSuccessMsg;
        return m_errorString;
}

inline ExitStatus::operator bool() const { return success(); }

inline bool ExitStatus::success() const { return (m_errorString[0] == 0); }

