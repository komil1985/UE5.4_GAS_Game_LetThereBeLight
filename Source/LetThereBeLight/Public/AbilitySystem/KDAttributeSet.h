// Copyright ASKD Games

#pragma once
	
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "KDAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class LETTHEREBELIGHT_API UKDAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UKDAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	UPROPERTY(BlueprintReadonly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UKDAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UKDAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadonly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UKDAttributeSet, Mana);

	UPROPERTY(BlueprintReadonly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UKDAttributeSet, MaxMana);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

};
