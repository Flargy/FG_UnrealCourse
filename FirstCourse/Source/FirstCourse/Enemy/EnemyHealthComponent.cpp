#include "EnemyHealthComponent.h"


void UEnemyHealthComponent::TakeDamage(float Damage)
{
	Health -= Damage;
	
	if (Health <= 0.f)
	{
		OnDeath.Broadcast();
	}
}