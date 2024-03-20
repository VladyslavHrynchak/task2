#include <iostream>

#include <condition_variable>
#include <mutex>
#include <random>
#include <chrono>
#include <thread>

std::condition_variable cv;
std::mutex m;

struct Point3D
{
public:

    friend std::ostream &operator<<(std::ostream& os, const Point3D& p){
        std::cout << p.x << "   " << p.y << "   " << p.z;
        return os;
    }

    double x, y, z;
};

Point3D original_p;

Point3D current_p;

double generate_deviation(const double &min, const double &max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distr(min, max);
    return distr(gen);
}

void set_random_deviation()
{
    Point3D deviation;

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lock(m);

            current_p.x += (deviation.x = generate_deviation(-1.0, 1.0));
            current_p.y += (deviation.y = generate_deviation(-1.0, 1.0));
            current_p.z += (deviation.z = generate_deviation(-1.0, 1.0));

            std::cout << "Deviation: " << deviation << std::endl ;
        }

        cv.notify_one();
    }
}

void return_to_original_position()
{
    while(true){
        std::unique_lock lk(m);
        cv.wait(lk);

        std::cout << "Current position: " << current_p << std::endl;
        current_p = original_p;
        std::cout << "Current position after reset: " << current_p << std::endl << std::endl;

        lk.unlock();
    }
}

int main()
{
    std::cout << "Enter x: ";
    std::cin >> original_p.x;

    std::cout << "Enter y: ";
    std::cin >> original_p.y;

    std::cout << "Enter z: ";
    std::cin >> original_p.z;

    current_p = original_p;

    std::cout << "Current position: " << current_p << std::endl << std::endl;

    std::thread th1(set_random_deviation);

    std::thread th2(return_to_original_position);

    th1.join();
    th2.join();

    return 0;
}
