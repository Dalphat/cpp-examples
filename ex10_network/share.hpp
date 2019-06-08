#ifndef SHARE_HPP
#define SHARE_HPP

#include <mutex>
namespace my {
    //Simple class that provides self locking on function member access.
    //Note: Prolonged locks should be handled by owner rather than this class.
    template <class T>
    class Share {
    private:
        T var;
        std::mutex mutex;
    public:
        Share(){}
        Share(const T& var) : var{ var } {}

        //Basic get/set function calls:
        T get() {
            T temp;
            mutex.lock();
            temp = var;
            mutex.unlock();
            return temp;//Returns a copy of member
        }
        void set(const T& var) {
            mutex.lock();
            this->var = var;
            mutex.unlock();
        }

        //Basic operator function calls:
        //explicit operator bool() { return get(); }


        explicit operator T() { return get(); }
        void operator=(const T& var) { set(var); }
        bool operator==(const T& var) { return get() == var; }
    };
};

#endif // !SHARE_HPP
