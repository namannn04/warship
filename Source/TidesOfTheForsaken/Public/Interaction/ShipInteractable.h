#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShipInteractable.generated.h"

class ACaptainCharacter;

/** One physical interaction contract for helm, cannon, ladder, storage and crew. */
UINTERFACE(MinimalAPI)
class UShipInteractable : public UInterface
{
    GENERATED_BODY()
};

class TIDESOFTHEFORSAKEN_API IShipInteractable
{
    GENERATED_BODY()

public:
    virtual bool CanInteract(const ACaptainCharacter* Captain) const = 0;
    virtual FText GetInteractionText() const = 0;
    virtual void Interact(ACaptainCharacter* Captain) = 0;
};
