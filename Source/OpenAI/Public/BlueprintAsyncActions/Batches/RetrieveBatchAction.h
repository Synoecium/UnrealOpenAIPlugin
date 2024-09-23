// OpenAI, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Provider/Types/BatchTypes.h"
#include "Provider/CommonTypes.h"
#include "RetrieveBatchAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRetrieveBatch, const FRetrieveBatchResponse&, Response, const FOpenAIError&, RawError);

class UOpenAIProvider;

UCLASS()
class URetrieveBatchAction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnRetrieveBatch OnCompleted;

    virtual void Activate() override;

private:
    /**
     * @param URLOverride Allows for the specification of a custom endpoint. This is beneficial when using a proxy.
     * If this functionality is not required, this parameter can be left blank.
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "OpenAI | Batches")
    static URetrieveBatchAction* RetrieveBatch(const FString& BatchID, const FOpenAIAuth& Auth, const FString& URLOverride);

    void TryToOverrideURL(UOpenAIProvider* Provider);

    void OnRetrieveBatchCompleted(const FRetrieveBatchResponse& Response);
    void OnRequestError(const FString& URL, const FString& Content);

private:
    FOpenAIAuth Auth;
    FString BatchID;
    FString URLOverride{};
};
