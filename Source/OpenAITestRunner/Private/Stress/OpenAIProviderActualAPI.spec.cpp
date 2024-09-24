// OpenAI, Copyright LifeEXE. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Provider/OpenAIProvider.h"
#include "Provider/Types/ModelTypes.h"
#include "Provider/Types/CommonTypes.h"
#include "Provider/Types/ModelTypes.h"
#include "FuncLib/OpenAIFuncLib.h"
#include "Algo/ForEach.h"
#include "TestUtils.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogOpenAIProviderActual, All, All);

BEGIN_DEFINE_SPEC(FOpenAIProviderActual, "OpenAI.Provider",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::StressFilter | EAutomationTestFlags::HighPriority)
TObjectPtr<UOpenAIProvider> OpenAIProvider;
FOpenAIAuth Auth;
bool RequestCompleted{false};
END_DEFINE_SPEC(FOpenAIProviderActual)

using namespace OpenAI::Tests;

namespace
{
const FString JobID = "ftjob-HwfVFJki16yQveB1iwPqBaeF";
const FString FileID = "file-xm3aonDNpFhE4CMnzUdgoKUU";
const int32 FileBytes = 3138;

struct FFineTunePayload
{
    FString JobID;
    FString FileID;
    FString ModelName;
    FString OrgId;
};

void TestFineTuningJob(FAutomationTestBase* Test, const FFineTuningJobObjectResponse& Response, const FFineTunePayload& Payload)
{
    if (!Test)
    {
        UE_LOGFMT(LogOpenAIProviderActual, Error, "Automation test object is invalid");
        return;
    }

    Test->TestTrue("Object should be valid", Response.Object.Equals("fine_tuning.job"));
    // Test->TestTrue("Model should be valid", Response.Model.Equals(Payload.ModelName));
    Test->TestTrue("Created_At should be valid", Response.Created_At > 0);
    Test->TestTrue("Organization_ID should be valid", Response.Organization_ID.Equals(Payload.OrgId));
    Test->TestTrue("Training_File should be valid", !Response.Training_File.IsEmpty());
}

}  // namespace

void FOpenAIProviderActual::Define()
{
    Describe("ActualAPI",
        [this]()
        {
            BeforeEach(
                [this]()
                {
                    Auth = UOpenAIFuncLib::LoadAPITokensFromFile(FPaths::ProjectDir().Append("OpenAIAuth.ini"));
                    OpenAIProvider = NewObject<UOpenAIProvider>();
                    OpenAIProvider->SetLogEnabled(true);
                    OpenAIProvider->OnRequestError().AddLambda(
                        [&](const FString& URL, const FString& Content)
                        {
                            RequestCompleted = true;
                            AddError(FString::Format(TEXT("URL: {0} Content: {1}"), {URL, Content}));
                        });
                    RequestCompleted = false;
                });

            It("Fine-tuning.ListFineTuningJobsShouldResponseCorrectly",
                [this]()
                {
                    const FString OrgId = Auth.OrganizationID;
                    OpenAIProvider->OnListFineTuningJobsCompleted().AddLambda(
                        [&, OrgId](const FListFineTuningJobsResponse& Response)
                        {
                            TestTrueExpr(Response.Object.Equals("list"));
                            for (const auto& FineTune : Response.Data)
                            {
                                TestTrueExpr(!FineTune.Model.IsEmpty());
                                TestTrueExpr(FineTune.Object.Equals("fine_tuning.job"));
                                TestTrueExpr(FineTune.Organization_ID.Equals(OrgId));
                                TestTrueExpr(FineTune.Created_At > 0);
                            }
                            RequestCompleted = true;
                        });

                    OpenAIProvider->ListFineTuningJobs(Auth);
                    ADD_LATENT_AUTOMATION_COMMAND(FWaitForRequestCompleted(RequestCompleted));
                });

            It("Fine-tuning.CreateFineTuningJobShouldResponseCorrectly",
                [this]()
                {
                    FFineTunePayload Payload;
                    Payload.FileID = FileID;
                    Payload.ModelName = UOpenAIFuncLib::OpenAIAllModelToString(EAllModelEnum::GPT_3_5_Turbo);
                    Payload.OrgId = Auth.OrganizationID;

                    OpenAIProvider->OnCreateFineTuningJobCompleted().AddLambda(
                        [&, Payload](const FFineTuningJobObjectResponse& Response)
                        {
                            TestFineTuningJob(this, Response, Payload);
                            RequestCompleted = true;
                        });

                    FFineTuningJob FineTuningJob;
                    FineTuningJob.Model = Payload.ModelName;
                    FineTuningJob.Training_File = Payload.FileID;
                    OpenAIProvider->CreateFineTuningJob(FineTuningJob, Auth);
                    ADD_LATENT_AUTOMATION_COMMAND(FWaitForRequestCompleted(RequestCompleted));
                });

            It("Fine-tuning.RetriveFineTuningJobShouldResponseCorrectly",
                [this]()
                {
                    FFineTunePayload Payload;
                    Payload.JobID = JobID;
                    Payload.FileID = FileID;
                    Payload.ModelName = UOpenAIFuncLib::OpenAIAllModelToString(EAllModelEnum::GPT_3_5_Turbo);
                    Payload.OrgId = Auth.OrganizationID;

                    OpenAIProvider->OnRetrieveFineTuningJobCompleted().AddLambda(
                        [&, Payload](const FFineTuningJobObjectResponse& Response)
                        {
                            TestFineTuningJob(this, Response, Payload);
                            TestTrueExpr(Response.ID.Equals(Payload.JobID));
                            RequestCompleted = true;
                        });

                    OpenAIProvider->RetrieveFineTuningJob(JobID, Auth);
                    ADD_LATENT_AUTOMATION_COMMAND(FWaitForRequestCompleted(RequestCompleted));
                });

            It("Fine-tuning.CancelFineTuningJobShouldResponseCorrectly",
                [this]()
                {
                    OpenAIProvider->OnCancelFineTuningJobCompleted().AddLambda(
                        [&](const FFineTuningJobObjectResponse& Response) { RequestCompleted = true; });

                    OpenAIProvider->CancelFineTuningJob(JobID, Auth);
                    ADD_LATENT_AUTOMATION_COMMAND(FWaitForRequestCompleted(RequestCompleted));
                });

            It("Fine-tuning.ListFineTuningEventsShouldResponseCorrectly",
                [this]()
                {
                    OpenAIProvider->OnListFineTuningEventsCompleted().AddLambda(
                        [&](const FFineTuningJobEventResponse& Response) { RequestCompleted = true; });

                    OpenAIProvider->ListFineTuningEvents(JobID, Auth);
                    ADD_LATENT_AUTOMATION_COMMAND(FWaitForRequestCompleted(RequestCompleted));
                });
        });
}

#endif
