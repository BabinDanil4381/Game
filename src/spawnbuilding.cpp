#include "spawnbuilding.h"

SpawnBuilding::SpawnBuilding(int x, int y) {
    coord_x = x;
    coord_y = y;
    building_position = new Point(x, y, build);

}

SpawnBuilding::~SpawnBuilding()
{
    delete building_position;
}

int SpawnBuilding::get_coord_x() const
{
    return coord_x;
}

int SpawnBuilding::get_coord_y() const
{
    return coord_y;
}

void SpawnBuilding::spawn(Enemy& comp, int x, int y)
{
    comp.spawn_enemy(x, y);
    comp.recovery_health();
}
