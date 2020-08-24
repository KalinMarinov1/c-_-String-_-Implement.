#include "kstring_h.h"

namespace kalin {
    size_t stringlength(const char *s) {
        if (s == nullptr)
            throw std::bad_alloc();

        size_t count = 0;
        while (*s != '\0') {
            ++count;
            *(++s);
        }
        return count;
    }

    size_t getcapacity(size_t stringsize, size_t currentcapacity) {
        while (stringsize > currentcapacity)
            currentcapacity <<= 1;                                     //multiply by 2

        return currentcapacity;
    }

// ********************* Member functions *********************



    Kstring::Kstring() : strsize_{0}, currentcapacity_{_defaultsize}, ptrtoarr_{nullptr} {}


    Kstring::Kstring(const char *text) : strsize_{stringlength(text)}, currentcapacity_{_defaultsize},
                                         ptrtoarr_{nullptr} {
        currentcapacity_ = getcapacity(strsize_, currentcapacity_);
        ptrtoarr_ = new char[currentcapacity_];
        std::memcpy(ptrtoarr_, text, strsize_);
    }


    Kstring::Kstring(const Kstring &text) : strsize_{text.strsize_}, currentcapacity_{text.currentcapacity_} {
        ptrtoarr_ = new char[currentcapacity_];
        std::memcpy(ptrtoarr_, text.ptrtoarr_, strsize_);
    }


    Kstring::Kstring(char text) : strsize_{1}, currentcapacity_{_defaultsize} {
        ptrtoarr_ = new char[currentcapacity_];
        *ptrtoarr_ = text;
    }


    Kstring::Kstring(Kstring &&s) noexcept: strsize_(s.strsize_), currentcapacity_(s.currentcapacity_),ptrtoarr_(s.ptrtoarr_) {
        s.ptrtoarr_ = nullptr;
        s.strsize_ = 0;
        s.currentcapacity_ = 0;
    }


    Kstring::~Kstring() {
        delete[] ptrtoarr_;
    }


/*
 * Return -1 if str1 < than str2 ,   return 0 if equal   , return 1 if str1 > str2
 *
 * first i check for nullptrs. after that i start iterating until they either become != or null.
 *
 * check for end of string or equality being tested at the end.
 *
 * */

    int Kstring::compare(const char *str1, const char *str2) {
        if (str1 == nullptr || str2 == nullptr)
            return str1 == nullptr ? -1 : 1;          //if str1 is null, then str2 is bigger, else str1 is bigger

        size_t iterator = 0;

        for (; iterator < SIZE_MAX; ++iterator) {
            if (str1[iterator] == '\0' || str2[iterator] == '\0')         //if 1 of them has finished
                break;
            if (str1[iterator] != str2[iterator])                         //if different chars
                return str1[iterator] > str2[iterator] ? 1 : -1;
        }

        if (str1[iterator] == '\0' && str2[iterator] == '\0')
            return 0;
        if (str1[iterator] != '\0')
            return 1;
        else
            return -1;
    }


    bool Kstring::compare(const Kstring &rhs) const {
        return *this == rhs;
    }


    size_t Kstring::size() const noexcept {
        return strsize_;
    }


    size_t Kstring::length() const noexcept {
        return sizeof(*ptrtoarr_) * strsize_;
    }


    size_t Kstring::capacity() const noexcept {
        return currentcapacity_;
    }


    char &Kstring::at(size_t idx) {
        if (idx >= strsize_ || idx < 0)
            throw std::range_error("Out of range");
        return ptrtoarr_[idx];
    }


    const char &Kstring::at(size_t idx) const {
        if (idx >= strsize_ || idx < 0)
            throw std::range_error("Out of range");
        return ptrtoarr_[idx];
    }


    bool Kstring::empty() const noexcept {
        return strsize_ == 0;
    }


    void Kstring::clear() noexcept {           //have to have a length of 0 .
        char* temp = new char[currentcapacity_];
        currentcapacity_ = 15;
        strsize_ = 0;
        std::swap(ptrtoarr_,temp);
        delete[] temp;
    }


    char &Kstring::back() {
        if (strsize_ != 0)
            return ptrtoarr_[strsize_ - 1];
        throw std::range_error("There are no elements in the string");
    }


    const char &Kstring::back() const {
        if (strsize_ != 0)
            return ptrtoarr_[strsize_ - 1];
        throw std::range_error("There are no elements in the string");
    }


    char &Kstring::front() {
        if (strsize_ != 0)
            return ptrtoarr_[0];
        throw std::range_error("There are no elements in the string");
    }


    const char &Kstring::front() const {
        if (strsize_ != 0)
            return ptrtoarr_[0];
        throw std::range_error("There are no elements in the string");
    }


    bool Kstring::find(const char *rhs) const {              //possible optimization with Knuth-Morris-Pratt algo
        size_t rhssize{stringlength(rhs)};
        if (rhssize > strsize_)
            return false;

        for (size_t iterator = 0; iterator <= strsize_ - rhssize; ++iterator) {
            if (*ptrtoarr_ == *rhs) {                                //if first letter match, then compare the whole str.
                if (Kstring::compare(&ptrtoarr_[iterator], &rhs[iterator]) == 0)
                    return true;
            }
        }
        return false;
    }


    bool Kstring::find(const Kstring &rhs) const {
        if (strsize_ < rhs.strsize_)              //early return if searched string is bigger
            return false;

        return find(rhs.ptrtoarr_);
    }


    bool Kstring::find(char rhs) const {
        while (*ptrtoarr_ != '\0') {
            if (*ptrtoarr_ == rhs)
                return true;
        }
        return false;
    }


    Kstring &Kstring::assign(const Kstring &rhs, size_t NumChars) {
        *this = rhs;
        memset(ptrtoarr_ + (NumChars * sizeof(char)), 0, (currentcapacity_ - NumChars) - 1);
        *(ptrtoarr_ + NumChars * sizeof(char)) = '\0';
        return *this;
    }


    Kstring &Kstring::assign(const Kstring &rhs) {
        *this = rhs;
        return *this;
    }

    Kstring &Kstring::assign(Kstring &&rhs) {
        *this = std::move(rhs);
        return *this;
    }

    Kstring &Kstring::assign(const char *rhs) {
        Kstring temp{rhs};
        *this = temp;
        return *this;
    }


    Kstring &Kstring::assign(char rhs) {
        *this = rhs;
        return *this;
    }


    Kstring &Kstring::append(char rhs) {
        *this += rhs;
        return *this;
    }


    Kstring &Kstring::append(const char *rhs) {
        *this += rhs;
        return *this;
    }


    Kstring &Kstring::append(const Kstring &rhs) {
        *this += rhs;
        return *this;
    }

/*
 * Appends a copy of a substring of str. The substring is the portion of str that begins at the
 * character position subpos and spans sublen characters (or until the end of str, if either str is too
 * short or if sublen is string::npos).
 * --Copied from cppreference.com
 * */
    Kstring &Kstring::append(const Kstring &rhs, size_t subpos, size_t subspan) {
        char *temp = new char[subspan];
        std::memcpy(temp, rhs.ptrtoarr_ + subpos - 1, sizeof(char) * subspan);
        *this += temp;
        return *this;
    }


    Kstring &Kstring::insert(size_t pos, const char *rhs) {
        --pos;                                                             //set it accordingly to array style numeration.

        if (pos > strsize_ || pos < 1)                                     //if bad range.
            throw std::range_error("Trying to insert out of the string");

        size_t rhssize{stringlength(rhs)};
        if (rhssize + strsize_ >= currentcapacity_)                       //if new allocation is needed
            throw std::out_of_range("The inserted string is too big");

        if (pos == strsize_-1)                           //if insert at the end.
            return (*this = assign(rhs));

        char *temp = new char[strsize_ -pos];                               //string which will take the right part of pre-inserted str.
        std::memcpy(temp, ptrtoarr_ + pos, sizeof(char) * strsize_ - pos);
        std::memcpy(ptrtoarr_ + pos, rhs, sizeof(char) * rhssize);
        std::memcpy(ptrtoarr_ + pos + rhssize, temp, sizeof(char) * strsize_ - pos);
        delete[] temp;
        strsize_ += rhssize;
        return *this;
    }


    Kstring &Kstring::insert(size_t pos, const Kstring &rhs) {
        return *this = insert(pos, rhs.ptrtoarr_);
    }


    Kstring &Kstring::insert(size_t pos, char rhs) {
        return *this = insert(pos, &rhs);
    }


    void Kstring::swap(Kstring &rhs) {
        std::swap(*this, rhs);
    }


// ** OPERATORS **
    std::ostream &operator<<(std::ostream &os, const Kstring &s)           //output operator
    {
        os.write(s.ptrtoarr_, s.strsize_);
        return os;
    }


    std::istream &operator>>(std::istream &is, Kstring &s) {              //input operator
        std::memset(s.ptrtoarr_, 0, sizeof(*s.ptrtoarr_));
        is >> std::ws;     //skips whitespace
        char ch = ' ';
        while (is.get(ch) && !isspace(ch))
            s += ch;
        return is;
    }


    Kstring &Kstring::operator=(char rhs) {                  //copy assignment
        if (currentcapacity_ > 15)
            delete[] ptrtoarr_;

        strsize_ = 1;
        ptrtoarr_ = new char[_defaultsize];
        *ptrtoarr_ = rhs;
        currentcapacity_ = _defaultsize;
        return *this;
    }


    Kstring &Kstring::operator=(const char *rhs) {
        strsize_ = stringlength(rhs);
        if (strsize_ >= currentcapacity_) {
            delete[] ptrtoarr_;
            currentcapacity_ = getcapacity(strsize_, currentcapacity_);
            ptrtoarr_ = new char[currentcapacity_];
        }

        std::memcpy(ptrtoarr_, rhs, strsize_);
        return *this;
    }


    Kstring &Kstring::operator=(const Kstring &rhs) {
        if (this == &rhs)
            return *this;

        if (currentcapacity_ > rhs.strsize_)
            std::memcpy(ptrtoarr_, rhs.ptrtoarr_, rhs.strsize_);
        else {
            currentcapacity_ = getcapacity(rhs.strsize_, currentcapacity_);
            delete[] ptrtoarr_;
            ptrtoarr_ = new char[currentcapacity_];
            std::memcpy(ptrtoarr_, rhs.ptrtoarr_, rhs.strsize_);
        }
        return *this;
    }


    Kstring &Kstring::operator=(Kstring &&rhs) noexcept {           //move assignment
        if (this != &rhs)
            *this = std::move(rhs);

        return *this;
    }


    Kstring &Kstring::operator+=(const char *rhs)         //add at end of current string
    {
        size_t rhssize{stringlength(rhs)};
        size_t appropriate_capacity = getcapacity(strsize_ + rhssize, currentcapacity_);

        if (appropriate_capacity > currentcapacity_) {
            currentcapacity_ = appropriate_capacity;
            char *temp = new char[currentcapacity_];
            std::memcpy(temp, ptrtoarr_, strsize_ * sizeof(char));
            std::swap(ptrtoarr_, temp);
            delete[] temp;
        }

        std::memcpy(ptrtoarr_ + (strsize_ * sizeof(char)), rhs, rhssize);
        strsize_ += rhssize;

        return *this;
    }


    Kstring &Kstring::operator+=(char rhs) {
        if (strsize_ +1 < currentcapacity_)
            std::memcpy(ptrtoarr_+strsize_,&rhs,1);
        else {
            currentcapacity_ <<= 1;                                   //2x current size only for a rhs char.
            char* temp = new char[currentcapacity_];
            std::memcpy(temp,ptrtoarr_,strsize_);                     //add previous string
            std::memcpy(temp+strsize_,&rhs,1);               //add rhs char.
            std::swap(temp,ptrtoarr_);
            delete [] temp;
        }
        ++strsize_;
        return *this;
    }


    Kstring &Kstring::operator+=(const Kstring &rhs) {
        if (strsize_ +rhs.strsize_ < currentcapacity_)
            std::memcpy(ptrtoarr_+strsize_,rhs.ptrtoarr_,rhs.strsize_);

        else {
           currentcapacity_ = getcapacity(strsize_+rhs.strsize_,currentcapacity_);
           char* temp = new char[currentcapacity_];
           std::memcpy(temp,ptrtoarr_,strsize_);
           std::memcpy(temp + strsize_,rhs.ptrtoarr_,rhs.strsize_);
           std::swap(temp,ptrtoarr_);
           delete [] temp;
        }
        strsize_ +=rhs.strsize_;
        return *this;
    }


    char &Kstring::operator[](int index) {
        return *(ptrtoarr_ + index);
    }


    const char &Kstring::operator[](int index) const {
        return *(ptrtoarr_ + index);
    }


// --------Friend functions--------

    Kstring operator+(const Kstring &lhs, const Kstring &rhs) {
        Kstring temp{lhs};
        temp += rhs;
        return temp;
    }


    Kstring operator+(const Kstring &lhs, const char *rhs) {
        Kstring temp{lhs};
        temp += rhs;
        return temp;
    }


    Kstring operator+(const Kstring &lhs, char rhs) {
        Kstring temp{lhs};
        temp += rhs;
        return temp;
    }


    Kstring operator+(char rhs, const Kstring &lhs) {
        Kstring temp{lhs};
        temp += rhs;
        return temp;
    }


    Kstring operator+(const char *rhs, const Kstring &lhs) {
        Kstring temp{lhs};
        temp += rhs;
        return temp;
    }


    bool operator==(const Kstring &lhs, const char *rhs) noexcept {
        if (lhs.strsize_ != stringlength(rhs))
            return false;

        return (Kstring::compare(lhs.ptrtoarr_, rhs) == 0);
    }


    bool operator==(const Kstring &lhs, const Kstring &rhs) noexcept {
        return (lhs.ptrtoarr_ == rhs.ptrtoarr_);
    }


    bool operator==(const Kstring &lhs, char rhs) noexcept {
        return (lhs.ptrtoarr_ == &rhs);
    }


    bool operator==(const char *rhs, const Kstring &lhs) noexcept {
        return (rhs == lhs.ptrtoarr_);
    }


    bool operator==(char rhs, const Kstring &lhs) noexcept {
        return (*lhs.ptrtoarr_ == rhs);
    }


    bool operator!=(const Kstring &lhs, const char *rhs) noexcept {
        if (lhs.strsize_ != stringlength(rhs))
            return true;

        return (Kstring::compare(lhs.ptrtoarr_, rhs) != 0);
    }


    bool operator!=(const Kstring &lhs, const Kstring &rhs) noexcept {
        return (lhs.ptrtoarr_ != rhs.ptrtoarr_);
    }


    bool operator!=(const Kstring &lhs, char rhs) noexcept {
        return (lhs.ptrtoarr_ != &rhs);
    }


    bool operator!=(const char *rhs, const Kstring &lhs) noexcept {
        return rhs != lhs.ptrtoarr_;
    }


    bool operator!=(char rhs, const Kstring &lhs) noexcept {
        return (&rhs != lhs.ptrtoarr_);
    }


    bool operator<(const Kstring &lhs, const char *rhs) {
        return (Kstring::compare(lhs.ptrtoarr_, rhs) == -1);
    }

    bool operator<(const Kstring &lhs, const Kstring &rhs) {
        return (lhs.ptrtoarr_ < rhs.ptrtoarr_);
    }


    bool operator<(const Kstring &lhs, char rhs) {
        return (lhs.ptrtoarr_ < (&rhs));
    }


    bool operator<(const char *rhs, const Kstring &lhs) {
        return (Kstring::compare(rhs, lhs.ptrtoarr_) == -1);
    }


    bool operator<(char rhs, const Kstring &lhs) {
        return (Kstring::compare(&rhs, lhs.ptrtoarr_) == -1);
    }


    bool operator>(const Kstring &lhs, const Kstring &rhs) {
        return (Kstring::compare(lhs.ptrtoarr_, rhs.ptrtoarr_) == 1);
    }


    bool operator>(const Kstring &lhs, const char *rhs) {
        return (Kstring::compare(lhs.ptrtoarr_, rhs) == 1);
    }


    bool operator>(const Kstring &lhs, char rhs) {
        return (Kstring::compare(lhs.ptrtoarr_, &rhs) == 1);
    }


    bool operator>(const char *rhs, const Kstring &lhs) {
        return (Kstring::compare(rhs, lhs.ptrtoarr_) == 1);
    }


    bool operator>(char rhs, const Kstring &lhs) {
        return (Kstring::compare(&rhs, lhs.ptrtoarr_) == 1);
    }


    using iterator = Kstring::iterator;

    iterator::iterator() : _ptr{nullptr}, _idx{0} {}


    iterator::iterator(Kstring *rhs, size_t pos) noexcept: _ptr{rhs}, _idx{pos} {}


    iterator::iterator(iterator &&rhs) noexcept: _ptr{rhs._ptr}, _idx{rhs._idx} {}



    iterator &iterator::operator=(iterator &&rhs) noexcept {
        _ptr = rhs._ptr;
        _idx = rhs._idx;
        return *this;
    }


    iterator &iterator::operator++() noexcept {
        ++_idx;
        return *this;
    }


    iterator &iterator::operator--() noexcept {
        --_idx;
        return *this;
    }


    bool iterator::operator==(const iterator &rhs) const noexcept {
        return ((_ptr == rhs._ptr) && (_idx == rhs._idx));
    }


    bool iterator::operator!=(const iterator &rhs) const noexcept {
        return ((_ptr != rhs._ptr) || (_idx != rhs._idx));
    }


    char &iterator::operator*() const {
        return (*_ptr)[_idx];
    }


    iterator Kstring::begin() {
        return iterator(this, 0);
    }


    iterator Kstring::end() {
        return iterator(this, strsize_);
    }


    using const_iterator = Kstring::const_iterator;

    const_iterator::const_iterator() : _ptr{nullptr}, _idx{0} {}


    const_iterator::const_iterator(const Kstring *rhs, size_t index) : _ptr{rhs}, _idx{index} {}


    const_iterator::const_iterator(const_iterator &&rhs) noexcept: _ptr{rhs._ptr}, _idx{rhs._idx} {}



    const_iterator &const_iterator::operator=(const_iterator &&rhs) noexcept {
        *this = rhs;
        return *this;
    }


    const_iterator &const_iterator::operator++() noexcept {
        ++_idx;
        return *this;
    }


    const_iterator &const_iterator::operator--() noexcept {
        ++_idx;
        return *this;
    }


    bool const_iterator::operator==(const const_iterator &rhs) const noexcept {
        return ((_ptr == rhs._ptr) && (_idx == rhs._idx));
    }


    bool const_iterator::operator!=(const const_iterator &rhs) const noexcept {
        return !(*this == rhs);
    }


    const char &const_iterator::operator*() const {
        return (*_ptr)[_idx];
    }


    const_iterator Kstring::cbegin() const {
        return const_iterator(this, 0);
    }


    const_iterator Kstring::cend() const {
        return const_iterator(this, strsize_);
    }

    using reverse_iterator = Kstring::reverse_iterator;

    reverse_iterator::reverse_iterator() : _ptr{nullptr}, _idx{0} {}


    reverse_iterator::reverse_iterator(Kstring *rhs, size_t index) noexcept: _ptr{rhs}, _idx{index} {}


    reverse_iterator::reverse_iterator(reverse_iterator &&rhs) noexcept: _ptr{rhs._ptr}, _idx{rhs._idx} {}


    reverse_iterator& reverse_iterator::operator=(reverse_iterator &&rhs) noexcept {
        _ptr = rhs._ptr;
        _idx = rhs._idx;
        return *this;
    }


    reverse_iterator &reverse_iterator::operator++() noexcept {
        --_idx;
        return *this;
    }


    reverse_iterator &reverse_iterator::operator--() noexcept {
        ++_idx;
        return *this;
    }


    bool reverse_iterator::operator==(const reverse_iterator &rhs) const noexcept {
        return ((_ptr == rhs._ptr) && (_idx == rhs._idx));
    }


    bool reverse_iterator::operator!=(const reverse_iterator &rhs) const noexcept {
        return ((_ptr != rhs._ptr) || (_idx != rhs._idx));
    }


    char &reverse_iterator::operator*() const {
        return (*_ptr)[_idx];
    }


    reverse_iterator Kstring::rbegin() {
        return reverse_iterator(this, strsize_);
    }


    reverse_iterator Kstring::rend() {
        return reverse_iterator(this, 0);
    }


    using reverse_const_iterator = Kstring::reverse_const_iterator;


    reverse_const_iterator::reverse_const_iterator() : _ptr{nullptr}, _idx{0} {}


    reverse_const_iterator::reverse_const_iterator(reverse_const_iterator &&rhs) noexcept: _ptr{rhs._ptr},
                                                                                           _idx{rhs._idx} {}


    reverse_const_iterator::reverse_const_iterator(const Kstring *rhs, size_t pos) : _ptr{rhs}, _idx{pos} {}




    reverse_const_iterator& reverse_const_iterator::operator=(reverse_const_iterator &&rhs) noexcept {
        _ptr = rhs._ptr;
        _idx = rhs._idx;
        return *this;
    }


    reverse_const_iterator &reverse_const_iterator::operator++() noexcept {
        --_idx;
        return *this;
    }


    reverse_const_iterator &reverse_const_iterator::operator--() noexcept {
        ++_idx;
        return *this;
    }


    bool reverse_const_iterator::operator==(const reverse_const_iterator &rhs) const noexcept {
        return ((_ptr == rhs._ptr) && (_idx == rhs._idx));
    }


    bool reverse_const_iterator::operator!=(const reverse_const_iterator &rhs) const noexcept {
        return ((_ptr != rhs._ptr) || (_idx != rhs._idx));
    }


    const char &reverse_const_iterator::operator*() const {
        return (*_ptr)[_idx];
    }


    reverse_const_iterator Kstring::rcbegin() const {
        return reverse_const_iterator(this, strsize_);
    }


    reverse_const_iterator Kstring::rcend() const {
        return reverse_const_iterator(this, 0);
    }
}


