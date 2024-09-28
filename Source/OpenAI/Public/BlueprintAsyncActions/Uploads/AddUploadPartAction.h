// OpenAI, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Provider/Types/UploadTypes.h"
#include "Provider/Types/CommonTypes.h"
#include "AddUploadPartAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAddUploadPart, const FUploadPartObjectResponse&, Response, const FOpenAIError&, RawError);

class UOpenAIProvider;

UCLASS()
class UAddUploadPartAction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnAddUploadPart OnCompleted;

    virtual void Activate() override;

private:
    /**
     * @param URLOverride Allows for the specification of a custom endpoint. This is beneficial when using a proxy.
     * If this functionality is not required, this parameter can be left blank.
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "OpenAI | Embeddings")
    static UAddUploadPartAction* AddUploadPart(
        const FString& UploadId, const FAddUploadPart& UploadPartRequest, const FOpenAIAuth& Auth, const FString& URLOverride);

    void TryToOverrideURL(UOpenAIProvider* Provider);

    void OnAddUploadPartCompleted(const FUploadPartObjectResponse& Response);
    void OnRequestError(const FString& URL, const FString& Content);

private:
    FString UploadId;
    FAddUploadPart UploadPartRequest;
    FOpenAIAuth Auth;
    FString URLOverride{};
};
