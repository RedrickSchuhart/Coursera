#include "geo2d.h"
#include "game_object.h"

#include "test_runner.h"

#include <vector>
#include <memory>

using namespace std;
using namespace geo2d;
// Определите классы Unit, Building, Tower и Fence так, чтобы они наследовались от
// GameObject и реализовывали его интерфейс.

template <typename T>
struct Collider : GameObject {
    bool Collide(const GameObject& that) const final {
    // Статически приводим тип *this к типу const T&, потому что мы знаем,
    // что T — наш наследник (см. ниже)
        return that.CollideWith(static_cast<const T&>(*this));
    }
};


class Unit final : public Collider<Unit> {
public:
    Unit(Point position) : position_(position) {
    }
    Point GetGeometry1() const { return position_; }
    bool CollideWith(const Unit& that) const override{
        return geo2d::Collide(position_, that.GetGeometry1());
    }
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
private:
    Point position_;
};

class Building final : public Collider<Building> {
public:
    Building(Rectangle rect) : rectangle_(rect) {
    }
    Rectangle GetGeometry2() const { return rectangle_; }
    bool CollideWith(const Unit& that) const override{
        return geo2d::Collide(rectangle_, that.GetGeometry1());
    }
    bool CollideWith(const Building& that) const override {
        return geo2d::Collide(rectangle_, that.GetGeometry2());
    }
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
private:
    Rectangle rectangle_;
};

class Tower final : public Collider<Tower> {
public:
    Tower(Circle circ) : circle_(circ) {
    }
    Circle GetGeometry3() const { return circle_; }
    bool CollideWith(const Unit& that) const override{
        return geo2d::Collide(circle_, that.GetGeometry1());
    }
    bool CollideWith(const Building& that) const override {
        return geo2d::Collide(circle_, that.GetGeometry2());
    }
    bool CollideWith(const Tower& that) const override {
        return geo2d::Collide(circle_, that.GetGeometry3());
    }
    bool CollideWith(const Fence& that) const override;
private:
    Circle circle_;
};

class Fence final : public Collider<Fence> {
public:
    Fence(Segment segm) : segment_(segm) {
    }
    Segment GetGeometry4() const { return segment_; }
    bool CollideWith(const Unit& that) const override{
        return geo2d::Collide(segment_, that.GetGeometry1());
    }
    bool CollideWith(const Building& that) const override {
        return geo2d::Collide(segment_, that.GetGeometry2());
    }
    bool CollideWith(const Tower& that) const override {
        return geo2d::Collide(segment_, that.GetGeometry3());
    }
    bool CollideWith(const Fence& that) const override {
        return geo2d::Collide(segment_, that.GetGeometry4());
    }
private:
    Segment segment_;
};


//
bool Unit::CollideWith(const Building& that) const{
    return geo2d::Collide(position_, that.GetGeometry2());
}
bool Unit::CollideWith(const Tower& that) const{
    return geo2d::Collide(position_, that.GetGeometry3());
}
bool Unit::CollideWith(const Fence& that) const{
    return geo2d::Collide(position_, that.GetGeometry4());
}
//
bool Building::CollideWith(const Tower& that) const{
    return geo2d::Collide(rectangle_, that.GetGeometry3());
}
bool Building::CollideWith(const Fence& that) const{
    return geo2d::Collide(rectangle_, that.GetGeometry4());
}
//
bool Tower::CollideWith(const Fence& that) const{
    return geo2d::Collide(circle_, that.GetGeometry4());
}
// Реализуйте функцию Collide из файла GameObject.h

bool Collide(const GameObject& first, const GameObject& second) {
    return first.Collide(second);
}

void TestAddingNewObjectOnMap() {
  // Юнит-тест моделирует ситуацию, когда на игровой карте уже есть какие-то объекты,
  // и мы хотим добавить на неё новый, например, построить новое здание или башню.
  // Мы можем его добавить, только если он не пересекается ни с одним из существующих.
  using namespace geo2d;

  cout << Collide(Rectangle{{11, 4}, {14, 6}}, Rectangle{{11, 4}, {14, 6}}) << endl;
  const vector<shared_ptr<GameObject>> game_map = {
    make_shared<Unit>(Point{3, 3}),
    make_shared<Unit>(Point{5, 5}),
    make_shared<Unit>(Point{3, 7}),
    make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
    make_shared<Tower>(Circle{Point{9, 4}, 1}),
    make_shared<Tower>(Circle{Point{10, 7}, 1}),
    make_shared<Building>(Rectangle{{11, 4}, {14, 6}})
  };

  for (size_t i = 0; i < game_map.size(); ++i) {
    Assert(
      Collide(*game_map[i], *game_map[i]),
      "An object doesn't collide with itself: " + to_string(i)
    );

    for (size_t j = 0; j < i; ++j) {
      Assert(
        !Collide(*game_map[i], *game_map[j]),
        "Unexpected collision found " + to_string(i) + ' ' + to_string(j)
      );
    }
  }

  auto new_warehouse = make_shared<Building>(Rectangle{{4, 3}, {9, 6}});
  ASSERT(!Collide(*new_warehouse, *game_map[0]));
  ASSERT( Collide(*new_warehouse, *game_map[1]));
  ASSERT(!Collide(*new_warehouse, *game_map[2]));
  ASSERT( Collide(*new_warehouse, *game_map[3]));
  ASSERT( Collide(*new_warehouse, *game_map[4]));
  ASSERT(!Collide(*new_warehouse, *game_map[5]));
  ASSERT(!Collide(*new_warehouse, *game_map[6]));

  auto new_defense_tower = make_shared<Tower>(Circle{{8, 2}, 2});
  ASSERT(!Collide(*new_defense_tower, *game_map[0]));
  ASSERT(!Collide(*new_defense_tower, *game_map[1]));
  ASSERT(!Collide(*new_defense_tower, *game_map[2]));
  ASSERT( Collide(*new_defense_tower, *game_map[3]));
  ASSERT( Collide(*new_defense_tower, *game_map[4]));
  ASSERT(!Collide(*new_defense_tower, *game_map[5]));
  ASSERT(!Collide(*new_defense_tower, *game_map[6]));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestAddingNewObjectOnMap);
  return 0;
}
