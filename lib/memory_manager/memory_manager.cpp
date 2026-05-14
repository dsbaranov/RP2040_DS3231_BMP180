#include "memory_manager.h"

void MemoryManager::set_max_pressure_bmp180(double value)
{
    bmp180__ref_.setMax(value);
}

void MemoryManager::set_min_pressure_bmp180(double value)
{
    bmp180__ref_.setMin(value);
}
