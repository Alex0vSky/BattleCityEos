#ifndef __acmeI_h__
#define __acmeI_h__

#include <acme.h>

namespace Acme
{

class BulletMix2I : public virtual BulletMix2
{
public:

    virtual ::std::shared_ptr<Bullet2> get() override;

    virtual void set(::std::shared_ptr<Bullet2>);
};

}

#endif
