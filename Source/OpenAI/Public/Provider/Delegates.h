// OpenAI, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Provider/Types/AllTypesHeader.h"

// ============================ C++ delegates ============================
// common
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequestCompleted, const FString& /* URL */, const FString& /* Response content */);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequestProgresses, const FString& /* URL */, const FString& /* Response content */);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequestError, const FString& /* URL */, const FString& /* Response content */);
// models
DECLARE_MULTICAST_DELEGATE_OneParam(FOnListModelsCompleted, const FListModelsResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRetrieveModelCompleted, const FRetrieveModelResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeleteFineTunedModelCompleted, const FDeleteFineTunedModelResponse&);
// chat
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateCompletionCompleted, const FCompletionResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateCompletionStreamCompleted, const TArray<FCompletionStreamResponse>&);
using FOnCreateCompletionStreamProgresses = FOnCreateCompletionStreamCompleted;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateChatCompletionCompleted, const FChatCompletionResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateChatCompletionStreamCompleted, const TArray<FChatCompletionStreamResponse>&);
using FOnCreateChatCompletionStreamProgresses = FOnCreateChatCompletionStreamCompleted;
// images
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateImageCompleted, const FImageResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateImageEditCompleted, const FImageEditResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateImageVariationCompleted, const FImageVariationResponse&);
// embeddings
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateEmbeddingsCompleted, const FEmbeddingsResponse&);
// audio + speech
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateSpeechCompleted, const FSpeechResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateAudioTranscriptionCompleted, const FAudioTranscriptionResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateAudioTranscriptionVerboseCompleted, const FAudioTranscriptionVerboseResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateAudioTranslationCompleted, const FAudioTranslationResponse&);
// files
DECLARE_MULTICAST_DELEGATE_OneParam(FOnListFilesCompleted, const FListFilesResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUploadFileCompleted, const FUploadFileResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeleteFileCompleted, const FDeleteFileResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRetrieveFileCompleted, const FRetrieveFileResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRetrieveFileContentCompleted, const FRetrieveFileContentResponse&);
// fine tunes
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateFineTuningJobCompleted, const FFineTuningJobObjectResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnListFineTuningJobsCompleted, const FListFineTuningJobsResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnListFineTuningEventsCompleted, const FListFineTuningEventsResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnListFineTuningCheckpointsCompleted, const FListFineTuningCheckpointsResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRetrieveFineTuningJobCompleted, const FFineTuningJobObjectResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCancelFineTuningJobCompleted, const FFineTuningJobObjectResponse&);
// moderations
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateModerationsCompleted, const FModerationsResponse&);
// batches
DECLARE_MULTICAST_DELEGATE_OneParam(FOnListBatchCompleted, const FListBatchResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateBatchCompleted, const FCreateBatchResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRetrieveBatchCompleted, const FRetrieveBatchResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCancelBatchCompleted, const FCancelBatchResponse&);
// uploads
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateUploadCompleted, const FUploadObjectResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddUploadPartCompleted, const FUploadPartObjectResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCompleteUploadCompleted, const FUploadObjectResponse&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCancelUploadCompleted, const FUploadObjectResponse&);
