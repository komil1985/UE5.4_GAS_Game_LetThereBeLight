// Copyright ASKD Games


#include "AbilitySystem/KDAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "Misc/KDGameplayTags.h"


UKDAttributeSet::UKDAttributeSet()
{
	//InitialPrimaryAttributes();
	//InitialSecondaryAttributes();
	//InitialVitalAttributes();

	const FKDGameplayTags& GameplayTags = FKDGameplayTags::Get();
	FAttributeSignature StrengthDelegate;
	StrengthDelegate.BindStatic(UKDAttributeSet::GetStrengthAttribute);

	TagsToAttribute.Add(GameplayTags.Attributes_Primary_Strength, StrengthDelegate);
}

void UKDAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, Vigor, COND_None, REPNOTIFY_Always);


	//Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);


	// Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKDAttributeSet, Mana, COND_None, REPNOTIFY_Always);
}


void UKDAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}


void UKDAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceAbilitySystemComponent = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceAbilitySystemComponent) && Props.SourceAbilitySystemComponent->AbilityActorInfo.IsValid() && Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController != nullptr)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.Get())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}


void UKDAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
}



// Primary Attributes
void UKDAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, Strength, OldStrength);
}
void UKDAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, Intelligence, OldIntelligence);
}
void UKDAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, Resilience, OldResilience);
}
void UKDAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, Vigor, OldVigor);
}



//Secondary Attributes
void UKDAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, Armor, OldArmor);
}
void UKDAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, ArmorPenetration, OldArmorPenetration);
}
void UKDAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, BlockChance, OldBlockChance);
}
void UKDAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, CriticalHitChance, OldCriticalHitChance);
}
void UKDAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}
void UKDAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}
void UKDAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, HealthRegeneration, OldHealthRegeneration);
}
void UKDAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, ManaRegeneration, OldManaRegeneration);
}
void UKDAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, MaxHealth, OldMaxHealth);
}
void UKDAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, MaxMana, OldMaxMana);
}


// Vital Attributes
void UKDAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, Health, OldHealth);
}
void UKDAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKDAttributeSet, Mana, OldMana);
}


void UKDAttributeSet::InitialPrimaryAttributes()
{
	// Setting primary attributes
	InitStrength(10.0f);
	InitIntelligence(20.0f);
	InitResilience(15.0f);
	InitVigor(10.0f);
}

void UKDAttributeSet::InitialSecondaryAttributes()
{
	// Setting secondary attributes
	InitArmor(10.0f);
	InitArmorPenetration(7.0f);
	InitCriticalHitChance(10.0f);
	InitCriticalHitDamage(15.0f);
	InitCriticalHitResistance(15.0f);
	InitBlockChance(12.0f);
	InitHealthRegeneration(15.0f);
	InitManaRegeneration(20.0f);
	InitMaxHealth(100.0f);
	InitMaxMana(100.0f);
}

void UKDAttributeSet::InitialVitalAttributes()
{
	// Setting vital attributes
	InitHealth(50.0f);
	InitMana(50.0f);
}

