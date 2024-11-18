#ifndef CRESULT_H
#define CRESULT_H
#include <vector>

//  --  Ogólny szablon  ------------------------------------------------------------------------------------------------

template <typename T, typename E> class CResult {
    public:
        CResult(const T &newValue) : value(new T(newValue)), errors(), success(true) {}
        CResult(E *error) : value(0), errors(1, error), success(false) {}
        CResult(std::vector<E*> *newErrors) : value(0), errors(newErrors), success(false) {}
        CResult(const CResult<T, E> &other) :
            value(other.value ? new T(*other.value) : 0),
            errors(other.errors),
            success(other.success) {}

        ~CResult() {
            delete value;

            for (typename std::vector<E*>::iterator it = errors.begin(); it != errors.end(); it++) {
                delete *it;
            }
        }

        static CResult<T, E> ok(const T &value) { return CResult<T, E>(value); }
        static CResult<T, E> fail(E *error) { return CResult<T, E>(error); }
        static CResult<T, E> fail(std::vector<E*> *errors) { return CResult<T, E>(errors); }

        CResult<T, E> &operator=(const CResult<T, E> &other) {
            if (this != &other) {
                delete value;

                for (typename std::vector<E*>::iterator it = errors.begin(); it != errors.end(); it++) {
                    delete *it;
                }

                value = other.value ? new T(*other.value) : 0;
                errors = other.errors;
                success = other.success;
            }

            return *this;
        }

        bool isSuccess() { return success; }

        T* getValue() {
            if (success && value) {
                return value;
            }

            return NULL;
        }
        std::vector<E*> &getErrors() {
            return errors;
        }

    private:
        T* value;
        std::vector<E*> errors;
        bool success;
};

//  --  Specjalizacja dla typu void ------------------------------------------------------------------------------------

template <typename E> class CResult<void, E> {
    public:
        CResult() : success(true) {}
        CResult(E *error) : errors(1, error), success(false) {}
        CResult(std::vector<E*> *errors) : errors(errors), success(false) {}
        CResult(const CResult<void, E> &other) : errors(other.errors), success(other.success) {}

        ~CResult() {
            for (typename std::vector<E*>::iterator it = errors.begin(); it != errors.end(); it++) {
                delete *it;
            }
        }

        static CResult<void, E> ok() { return CResult<void, E>(); }
        static CResult<void, E> fail(E *error) { return CResult<void, E>(error); }
        static CResult<void, E> fail(std::vector<E*> *errors) { return CResult<void, E>(errors); }

        CResult<void, E> &operator=(const CResult<void, E> &other) {
            if (this != &other) {
                for (typename std::vector<E*>::iterator it = errors.begin(); it != errors.end(); it++) {
                    delete *it;
                }

                errors = other.errors;
                success = other.success;
            }

            return *this;
        }

        bool isSuccess() { return success; }

        std::vector<E*> getErrors(std::vector<E*> *errors) {
            return errors;
        }

    private:
        std::vector<E*> errors;
        bool success;
};


#endif //CRESULT_H
