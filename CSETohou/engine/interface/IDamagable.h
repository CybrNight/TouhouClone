#ifndef IDAMAGABLE_H
#define IDAMAGABLE_H


class IDamagable
{
public:
    IDamagable();
    virtual ~IDamagable() = 0;
    virtual void Damage() = 0;
};

#endif // IDAMAGABLE_H
