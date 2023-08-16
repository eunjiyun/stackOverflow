#include "Monster.h"



Monster::Monster(const Monster& other)
{
    lock_guard<mutex> ll{ other.m_lock };
    Pos = other.Pos;
    room_num = other.room_num;
    alive = other.alive.load();
    BB = other.BB;
    m_id = other.m_id;
    type = other.type;
    HP = other.HP;
    power = other.power;
    view_range = other.view_range;
    speed = other.speed;
    curState = other.curState;
    recent_updateTime = other.recent_updateTime;
    distances = other.distances;
    target_id = other.target_id;
    attacked = other.attacked;
}

Monster& Monster::operator=(const Monster& other)
{
    if (this == &other) {
        return *this; 
    }
    lock_guard<mutex> l1{ this->m_lock };
    lock_guard<mutex> l2{ other.m_lock };
    Pos = other.Pos;
    room_num = other.room_num;
    alive = other.alive.load();
    BB = other.BB;
    m_id = other.m_id;
    type = other.type;
    HP = other.HP;
    power = other.power;
    view_range = other.view_range;
    speed = other.speed;
    curState = other.curState;
    recent_updateTime = other.recent_updateTime;
    distances = other.distances;
    target_id = other.target_id;
    attacked = other.attacked;
    return *this;
}

Monster::~Monster()
{
    //delete m_pool;
}

void Monster::Re_Initialize(short _type, XMFLOAT3 _pos)
{
    alive = false;
    Pos = _pos;
    curState = NPC_State::Idle;
    recent_updateTime = high_resolution_clock::now();
    for (auto& distance : distances) {
        distance.distance = 10000.f;
        distance._id = -1;
    }
    target_id = -1;
    attacked = false;
    switch (_type)
    {
    case 0: // �տ� Į
        HP = 250;
        dead_timer = 3.3f;
        attack_timer = attack_cycle;
        break;
    case 1: // ���ٱ� �ٸ�
        HP = 150;
        dead_timer = 3.3f;
        attack_timer = attack_cycle;
        break;
    case 2: // ������
        HP = 50;
        dead_timer = 3.3f;
        attack_timer = attack_cycle;
        break;
    case 3:
        HP = 2000;
        dead_timer = 3.3f;
        attack_timer = attack_cycle;
        break;
    case 4: // �ͽ�
        HP = 50;
        dead_timer = 3.3f;
        attack_timer = attack_cycle;
        break;
    case 5:
        HP = 500;
        dead_timer = 3.3f;
        attack_timer = attack_cycle;
        break;
    }
}
void Monster::Initialize(short _roomNum, short _id, short _type, XMFLOAT3 _pos) 
{
    alive = false;
    Pos = _pos;
    room_num = _roomNum;
    m_id = _id;
    curState = NPC_State::Idle;
    recent_updateTime = high_resolution_clock::now();
    for (auto& distance : distances) {
        distance.distance = 10000.f;
        distance._id = -1;
    }
    target_id = -1;
    attacked = false;
    switch (_type)
    {
    case 0: // �տ� Į
        type = 0;
        HP = 250;
        power = 60;
        view_range = 400;
        speed = 24.f;
        attack_range = 21.f;
        attack_cycle = (71.f / 30.f); // 2.366667��
        attack_timer = attack_cycle;
        BB = BoundingBox(_pos, MONSTER_SIZE);
        dead_timer = 3.3f;
        break;
    case 1: // ���ٱ� �ٸ�
        type = 1;
        HP = 150;
        power = 60;
        view_range = 400;
        speed = 24.f;
        attack_range = 15.f;
        attack_cycle = (56.f / 30.f); // 2.366667��
        attack_timer = attack_cycle;
        BB = BoundingBox(_pos, SMALL_MONSTER_SIZE);
        dead_timer = 3.3f;
        break;
    case 2: // ������
        type = 2;
        HP = 50;
        power = 150;
        view_range = 400;
        speed = 24.f;
        attack_range = 150.f;
        attack_cycle = (8.f / 3.f); // 2.666664��
        attack_timer = attack_cycle;
        BB = BoundingBox(_pos, SMALL_MONSTER_SIZE);
        dead_timer = 3.3f;
        break;
    case 3: // ���� ����
        type = 3;
        HP = 2000;
        power = 200;
        view_range = 100;
        speed = 24.f;
        attack_range = 75.f;
        attack_cycle = (10.f / 3.f); // 3.333333��
        attack_timer = attack_cycle;
        BB = BoundingBox(_pos, BOSS_MONSTER_SIZE);
        dead_timer = 1.f;
        break;
    }
}

