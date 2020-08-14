#ifndef UNTITLED3_KSTRING_H
#define UNTITLED3_KSTRING_H

#include <iostream>
#include <cstring>
#include <string>


namespace kalin {

    size_t stringlength(const char *s);                 //Return amount of chars in a given char*

    size_t getcapacity(size_t stringsize, size_t currentcapacity);     //Returns the appropriate capacity for an array

    const int Lengthunder15 = 15;


    class Kstring {
    private:
        size_t strsize_;                       //current string size.
        size_t currentcapacity_;               //the max size, which the array can take before resizing.
        char *ptrtoarr_;

    public:
        Kstring();

        explicit  Kstring(const char *);

        Kstring(const Kstring &);

        explicit Kstring(char);

        Kstring(Kstring &&) noexcept;

        ~Kstring();


        //****String main functions****
        static int compare(const char *str1,const char *str2);           //return -1 if str1 < str    || return 0 if equal   || return 1 if str1 > str2
        bool compare(const Kstring &rhs) const;

        size_t size() const noexcept;                           //return the size of string.
        size_t length() const noexcept;                         //return length of string
        size_t capacity() const noexcept;

        char &at(size_t idx);                                    //return the character at specific index.
        const char &at(size_t) const;

        bool empty() const noexcept;                             //Check if string is empty
        void clear() noexcept;                                   //Clears the string.
        char &back();                                            //Access of last element
        const char &back() const;

        char &front();                                           //Access the first element.
        const char &front() const;

        bool find(const char *rhs) const;                        //finds value from string.
        bool find(const Kstring &rhs) const;                     //a specific part of string.
        bool find(char rhs) const;                              //a single char.
        Kstring &assign(const Kstring &rhs, size_t NumChars);    //sets at specific position
        Kstring &assign(const Kstring &rhs);                     //replaces the old string
        Kstring &assign(Kstring &&rhs);

        Kstring &assign(const char *rhs);                       //assign a c-str
        Kstring &assign(char rhs);                              //a char.
        Kstring &append(const Kstring &rhs);                     //append Kstring at end.
        Kstring &append(const char *rhs);                        //append a c-str
        Kstring &append(char rhs);                               //append a single char.
        Kstring &append(const Kstring &rhs, size_t subpos,size_t subspan);     //append Kstring at subpos with subspan of letters from rhs.
        Kstring &insert(size_t pos, const Kstring &rhs);                         //insert Kstring at pos.
        Kstring &insert(size_t pos, const char *rhs);                            //insert c-str at pos.
        Kstring &insert(size_t pos, char);

        void swap(Kstring &rhs);                                                //swaps 2 Kstrings.

        //****Operators****

        Kstring &operator=(const char *);

        Kstring &operator=(char);

        Kstring &operator=(Kstring &&) noexcept;

        Kstring &operator=(const Kstring &);

        Kstring &operator+=(const char *);

        Kstring &operator+=(char);

        Kstring &operator+=(const Kstring &);

        char &operator[](int index);

        const char &operator[](int index) const;

        //****Friend functions****
        friend std::ostream &operator<<(std::ostream &os, const Kstring &s);

        friend std::istream &operator>>(std::istream &is, Kstring &s);

        friend Kstring operator+(const Kstring &lhs, const Kstring &rhs);

        friend Kstring operator+(const Kstring &lhs, const char *rhs);

        friend Kstring operator+(const Kstring &lhs, char rhs);

        friend Kstring operator+(char rhs, const Kstring &lhs);

        friend Kstring operator+(const char *rhs, const Kstring &lhs);

        friend bool operator==(const Kstring &lhs, const Kstring &rhs) noexcept;

        friend bool operator==(const Kstring &lhs, const char *rhs) noexcept;

        friend bool operator==(const Kstring &lhs, char rhs) noexcept;

        friend bool operator==(const char *rhs, const Kstring &lhs) noexcept;

        friend bool operator==(char rhs, const Kstring &lhs) noexcept;

        friend bool operator!=(const Kstring &lhs, const Kstring &rhs) noexcept;

        friend bool operator!=(const Kstring &lhs, const char *rhs) noexcept;

        friend bool operator!=(const Kstring &lhs, char rhs) noexcept;

        friend bool operator!=(const char *rhs, const Kstring &lhs) noexcept;

        friend bool operator!=(char rhs, const Kstring &lhs) noexcept;

        friend bool operator<(const Kstring &lhs, const Kstring &rhs);

        friend bool operator<(const Kstring &lhs, const char *rhs);

        friend bool operator<(const Kstring &lhs, char rhs);

        friend bool operator<(const char *rhs, const Kstring &lhs);

        friend bool operator<(char rhs, const Kstring &lhs);

        friend bool operator>(const Kstring &lhs, const Kstring &rhs);

        friend bool operator>(const Kstring &lhs, const char *rhs);

        friend bool operator>(const Kstring &lhs, char rhs);

        friend bool operator>(const char *rhs, const Kstring &lhs);

        friend bool operator>(char rhs, const Kstring &lhs);


        class iterator {
        private:
            Kstring *_ptr;
            size_t _idx;
        public:
            iterator();

            iterator(const iterator &rhs) = default;

            iterator(Kstring *rhs, size_t pos) noexcept;

            iterator(iterator &&rhs) noexcept;

            ~iterator();

            iterator &operator=(const iterator &rhs) = default;

            iterator &operator=(iterator &&rhs) noexcept;

            iterator &operator++() noexcept;

            iterator &operator--() noexcept;

            bool operator==(const iterator &rhs) const noexcept;

            bool operator!=(const iterator &rhs) const noexcept;

            char &operator*() const;
        };

        iterator begin();

        iterator end();


        class const_iterator {
        private:
            const Kstring *_ptr;
            size_t _idx;
        public:
            const_iterator();

            const_iterator(const const_iterator &rhs) = default;

            const_iterator(const Kstring *rhs, size_t index);

            const_iterator(const_iterator &&rhs) noexcept;

            ~const_iterator();

            const_iterator &operator=(const const_iterator &rhs) = default;

            const_iterator &operator=(const_iterator &&rhs) noexcept;

            const_iterator &operator++() noexcept;

            const_iterator &operator--() noexcept;

            bool operator==(const const_iterator &rhs) const noexcept;

            bool operator!=(const const_iterator &rhs) const noexcept;

            const char &operator*() const;
        };

        const_iterator cbegin() const;

        const_iterator cend() const;


        class reverse_iterator {
        private:
            Kstring *_ptr;
            size_t _idx;
        public:
            reverse_iterator();

            explicit reverse_iterator(Kstring *rhs = nullptr, size_t index = 0) noexcept;

            reverse_iterator(const reverse_iterator &rhs) = default;

            reverse_iterator(reverse_iterator &&rhs) noexcept;

            ~reverse_iterator();

            reverse_iterator &operator=(const reverse_iterator &rhs) = default;

            reverse_iterator &operator=(reverse_iterator &&rhs) noexcept;

            reverse_iterator &operator++() noexcept;

            reverse_iterator &operator--() noexcept;

            bool operator==(const reverse_iterator &rhs) const noexcept;

            bool operator!=(const reverse_iterator &rhs) const noexcept;

            char &operator*() const;
        };

        reverse_iterator rbegin();

        reverse_iterator rend();

        class reverse_const_iterator {
        private:
            const Kstring *_ptr;
            size_t _idx;
        public:
            reverse_const_iterator();

            explicit reverse_const_iterator(const Kstring *rhs = nullptr, size_t pos = 0);

            reverse_const_iterator(const reverse_const_iterator &rhs);

            reverse_const_iterator(reverse_const_iterator &&rhs) noexcept;

            ~reverse_const_iterator();

            reverse_const_iterator &operator=(const reverse_const_iterator &rhs) noexcept = default;

            reverse_const_iterator &operator=(reverse_const_iterator &&rhs) noexcept;

            reverse_const_iterator &operator++() noexcept;

            reverse_const_iterator &operator--() noexcept;

            bool operator==(const reverse_const_iterator &rhs) const noexcept;

            bool operator!=(const reverse_const_iterator &rhs) const noexcept;

            const char &operator*() const;
        };

        reverse_const_iterator rcbegin() const;

        reverse_const_iterator rcend() const;
    };

}

#endif //KSTRING_KSTRING_H
