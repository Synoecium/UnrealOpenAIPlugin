// OpenAI, Copyright LifeEXE. All Rights Reserved.

#include "BlueprintAsyncActions/FineTuning/CreateFineTuningJobAction.h"
#include "Provider/OpenAIProvider.h"
#include "API/API.h"

UCreateFineTuningJobAction* UCreateFineTuningJobAction::CreateFineTuningJob(
    const FFineTuningJob& FineTuningJob, const FOpenAIAuth& Auth, const FString& URLOverride)
{
    auto* CompletionAction = NewObject<UCreateFineTuningJobAction>();
    CompletionAction->FineTuningJob = FineTuningJob;
    CompletionAction->Auth = Auth;
    return CompletionAction;
}

void UCreateFineTuningJobAction::Activate()
{
    auto* Provider = NewObject<UOpenAIProvider>();
    Provider->OnCreateFineTuningJobCompleted().AddUObject(this, &ThisClass::OnCreateFineTuningJobCompleted);
    Provider->OnRequestError().AddUObject(this, &ThisClass::OnRequestError);
    TryToOverrideURL(Provider);
    Provider->CreateFineTuningJob(FineTuningJob, Auth);
}

void UCreateFineTuningJobAction::OnCreateFineTuningJobCompleted(const FFineTuningJobObjectResponse& Response)
{
    OnCompleted.Broadcast(Response, {});
}

void UCreateFineTuningJobAction::OnRequestError(const FString& URL, const FString& Content)
{
    OnCompleted.Broadcast({}, FOpenAIError{Content, true});
}

void UCreateFineTuningJobAction::TryToOverrideURL(UOpenAIProvider* Provider)
{
    if (URLOverride.IsEmpty()) return;

    OpenAI::V1::FOpenAIEndpoints Endpoints;
    Endpoints.FineTuningJobs = URLOverride;
    const auto API = MakeShared<OpenAI::V1::GenericAPI>(Endpoints);
    Provider->SetAPI(API);
}
