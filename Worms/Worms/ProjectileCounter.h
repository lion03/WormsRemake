#pragma once
class ProjectileCounter
{
public:
	
	virtual ~ProjectileCounter(void);

	static ProjectileCounter& getInstance(void){

		static ProjectileCounter m_ProjeCounter;

		return m_ProjeCounter;
		
	}

	void addProjecile(unsigned int burst = 1){m_ActiveProjectiles+=burst;}

	void removeProjectile(void){--m_ActiveProjectiles;}

	unsigned int getLiveProjectileCount(void) {return m_ActiveProjectiles;}

private:
	static unsigned int m_ActiveProjectiles;
	ProjectileCounter(void);
};

