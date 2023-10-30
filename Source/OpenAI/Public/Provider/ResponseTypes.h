// OpenAI, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonTypes.h"
#include "ResponseTypes.generated.h"

/*
    @todo: add more errors https://platform.openai.com/docs/guides/error-codes
*/
UENUM(BlueprintType)
enum class EOpenAIResponseError : uint8
{
    InvalidAPIKey = 0,
    NetworkError,
    ModelNotFound,
    Unknown
};

UENUM(BlueprintType)
enum class EOpenAIFinishReason : uint8
{
    Stop = 0,
    Length,
    Content_Filter,
    Function_Call,
    Null
};

USTRUCT(BlueprintType)
struct FOpenAIError
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString RawContent{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool WasError{false};
};

USTRUCT(BlueprintType)
struct FPermission
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_Create_Engine{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_Sampling{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_Logprobs{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_Search_Indices{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_View{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_Fine_Tuning{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Organization{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Group{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Is_Blocking{};
};

USTRUCT(BlueprintType)
struct FOpenAIModel
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Owned_By{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FPermission> Permission;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Root{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Parent{};
};

USTRUCT(BlueprintType)
struct FListModelsResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIModel> Data;
};

USTRUCT(BlueprintType)
struct FRetrieveModelResponse : public FOpenAIModel
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FBaseChoice
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Text{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Index{};
};

USTRUCT(BlueprintType)
struct FLogProbs
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FString> Tokens;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<double> Token_Logprobs;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Top_Logprobs{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<int32> Text_Offset;
};

USTRUCT(BlueprintType)
struct FChoice : public FBaseChoice
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FLogProbs LogProbs;

    /**
      The reason the model stopped generating tokens.
      This will be stop if the model hit a natural stop point or a provided stop sequence,
      length if the maximum number of tokens specified in the request was reached, or
      content_filter if content was omitted due to a flag from our content filters.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Finish_Reason{};
};

USTRUCT(BlueprintType)
struct FChatChoice
{
    GENERATED_BODY()

    /**
      The index of the choice in the list of choices.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Index{};

    /**
      A chat completion message generated by the model.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FMessage Message;

    /**
      The reason the model stopped generating tokens.
      This will be stop if the model hit a natural stop point or a provided stop sequence,
      length if the maximum number of tokens specified in the request was reached,
      content_filter if content was omitted due to a flag from our content filters,
      or function_call if the model called a function.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Finish_Reason{};
};

USTRUCT(BlueprintType)
struct FUsage
{
    GENERATED_BODY()

    /**
      Number of tokens in the prompt.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Prompt_Tokens{};

    /**
      Number of tokens in the generated completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Completion_Tokens{};

    /**
      Total number of tokens used in the request (prompt + completion).
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Total_Tokens{};
};

USTRUCT(BlueprintType)
struct FCompletionResponseBase
{
    GENERATED_BODY()

    /**
       A unique identifier for the completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID{};

    /**
       The object type, which is always "text_completion"
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    /**
       The Unix timestamp (in seconds) of when the completion was created.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    /**
       The model used for completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model{};

    /**
       The list of completion choices the model generated for the input prompt.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FChoice> Choices;
};

USTRUCT(BlueprintType)
struct FCompletionResponse : public FCompletionResponseBase
{
    GENERATED_BODY()

    /**
       Usage statistics for the completion request.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FUsage Usage;
};

USTRUCT(BlueprintType)
struct FCompletionStreamResponse : public FCompletionResponseBase
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FChatCompletionResponseBase
{
    GENERATED_BODY()

    /**
       A unique identifier for the chat completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    /**
       The object type, which is always chat.completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    /**
       The Unix timestamp (in seconds) of when the chat completion was created.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    /**
       The model used for the chat completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model;
};

USTRUCT(BlueprintType)
struct FChatCompletionResponse : public FChatCompletionResponseBase
{
    GENERATED_BODY()
    /**
       A list of chat completion choices. Can be more than one if n is greater than 1.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FChatChoice> Choices;

    /**
       Usage statistics for the completion request.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FUsage Usage;
};

USTRUCT(BlueprintType)
struct FDelta
{
    GENERATED_BODY()

    /**
       The contents of the chunk message.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Content{};

    /**
       The name and arguments of a function that should be called, as generated by the model.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FFunctionCall Function_Call;

    /**
       The role of the author of this message.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Role;
};

USTRUCT(BlueprintType)
struct FChatStreamChoice
{
    GENERATED_BODY()

    /**
       A chat completion delta generated by streamed model responses.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FDelta Delta{};

    /**
       The reason the model stopped generating tokens.
       This will be stop if the model hit a natural stop point or a provided stop sequence,
       length if the maximum number of tokens specified in the request was reached,
       content_filter if content was omitted due to a flag from our content filters, or
       function_call if the model called a function.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Finish_Reason{};

    /**
       The index of the choice in the list of choices.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Index{};
};

USTRUCT(BlueprintType)
struct FChatCompletionStreamResponse : public FChatCompletionResponseBase
{
    GENERATED_BODY()

    /**
       A list of chat completion choices. Can be more than one if n is greater than 1.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FChatStreamChoice> Choices;
};

USTRUCT(BlueprintType)
struct FEditResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FBaseChoice> Choices;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FUsage Usage;
};

USTRUCT(BlueprintType)
struct FImageResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FString> Data;
};

USTRUCT(BlueprintType)
struct FImageEditResponse : public FImageResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FImageVariationResponse : public FImageResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FEmbeddingsUsage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Prompt_Tokens{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Total_Tokens{};
};

USTRUCT(BlueprintType)
struct FEmbeddingsData
{
    GENERATED_BODY()

    /**
      The object type, which is always "embedding".
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    /**
      The index of the embedding in the list of embeddings.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Index{};

    /**
      The embedding vector, which is a list of floats. The length of vector depends on the model as listed in the embedding guide:
      https://platform.openai.com/docs/guides/embeddings
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<float> Embedding;
};

USTRUCT(BlueprintType)
struct FEmbeddingsResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FEmbeddingsData> Data;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FEmbeddingsUsage Usage;
};

USTRUCT(BlueprintType)
struct FAudioTranscriptionResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Text;
};

USTRUCT(BlueprintType)
struct FAudioTranslationResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Text;
};

USTRUCT(BlueprintType)
struct FOpenAIFile
{
    GENERATED_BODY()

    /**
      The file identifier, which can be referenced in the API endpoints.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    /**
      The object type, which is always "file".
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    /**
      The size of the file in bytes.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Bytes{};

    /**
      The Unix timestamp (in seconds) for when the file was created.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created_At{};

    /**
      The name of the file.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString FileName;

    /**
      The intended purpose of the file.
      Supported values are fine-tune or fine-tune-results.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Purpose;

    /**
      The current status of the file,
      which can be either uploaded, processed, pending, error, deleting or deleted.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Status;

    /**
      Additional details about the status of the file.
      If the file is in the error state,
      this will include a message describing the error.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Status_Details;
};

USTRUCT(BlueprintType)
struct FListFilesResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIFile> Data;
};

USTRUCT(BlueprintType)
struct FUploadFileResponse : public FOpenAIFile
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FDeleteFileResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Deleted{};
};

USTRUCT(BlueprintType)
struct FRetrieveFileResponse : public FOpenAIFile
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FRetrieveFileContentResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Content;
};

USTRUCT(BlueprintType)
struct FOpenAIEvent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created_At{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Level;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Message;
};

USTRUCT(BlueprintType)
struct FHyperparams
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Batch_Size{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    float Learning_Rate_Multiplier{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 N_Epochs{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    float Prompt_Loss_Weight{};
};

USTRUCT(BlueprintType)
struct FBaseFineTuneResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created_At{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Fine_Tuned_Model;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FHyperparams Hyperparams;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Organization_ID;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIFile> Result_Files;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Status;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIFile> Validation_Files;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIFile> Training_Files;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Updated_At{};
};

USTRUCT(BlueprintType)
struct FFineTuneResponse : public FBaseFineTuneResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIEvent> Events;
};

USTRUCT(BlueprintType)
struct FListFineTuneResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FBaseFineTuneResponse> Data;
};

USTRUCT(BlueprintType)
struct FFineTuneEventsResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIEvent> Data;
};

USTRUCT(BlueprintType)
struct FDeleteFineTuneResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Deleted{};
};

USTRUCT(BlueprintType)
struct FModerationCategories
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Hate{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Hate_Threatening{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Self_Harm{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Sexual{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Sexual_Minors{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Violence{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Violence_Graphic{};
};

USTRUCT(BlueprintType)
struct FModerationScores
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Hate{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Hate_Threatening{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Self_Harm{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Sexual{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Sexual_Minors{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Violence{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Violence_Graphic{};
};

USTRUCT(BlueprintType)
struct FModerationResults
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FModerationCategories Categories;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FModerationScores Category_Scores;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Flagged{};
};

USTRUCT(BlueprintType)
struct FModerationsResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FModerationResults> Results;
};

USTRUCT(BlueprintType)
struct FFineTuningJobHyperparams
{
    GENERATED_BODY()

    /**
      The number of epochs to train the model for.
      An epoch refers to one full cycle through the training dataset.
      "auto" decides the optimal number of epochs based on the size of the dataset.
      If setting the number manually, we support any number between 1 and 50 epochs.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString N_Epochs;
};

USTRUCT(BlueprintType)
struct FFineTuningJobError
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Code;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Param;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Message;
};

USTRUCT(BlueprintType)
struct FFineTuningJobObjectResponse
{
    GENERATED_BODY()

    /**
      The object identifier, which can be referenced in the API endpoints.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    /**
      The Unix timestamp (in seconds) for when the fine-tuning job was created.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created_At{};

    /**
      For fine-tuning jobs that have failed, this will contain more information on the cause of the failure.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FFineTuningJobError Error;

    /**
      The name of the fine-tuned model that is being created. The value will be null if the fine-tuning job is still running.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Fine_Tuned_Model;

    /**
      The Unix timestamp (in seconds) for when the fine-tuning job was finished.
      The value will be null if the fine-tuning job is still running.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Finished_At{};

    /**
      The hyperparameters used for the fine-tuning job:
      https://platform.openai.com/docs/guides/fine-tuning
      See the fine-tuning guide for more details.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FFineTuningJobHyperparams Hyperparameters;

    /**
      The size of the file in bytes.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model;

    /**
      The object type, which is always "fine_tuning.job".
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    /**
      The organization that owns the fine-tuning job.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Organization_ID;

    /**
      The compiled results file ID(s) for the fine-tuning job.
      You can retrieve the results with the Files API:
      https://platform.openai.com/docs/api-reference/files/retrieve-contents
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FString> Result_Files;

    /**
      The current status of the fine-tuning job,
      which can be either validating_files, queued, running, succeeded, failed, or cancelled.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Status;

    /**
      The total number of billable tokens processed by this fine-tuning job.
      The value will be null if the fine-tuning job is still running.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Trained_Tokens{};

    /**
      The file ID used for training. You can retrieve the training data with the Files API:
      https://platform.openai.com/docs/api-reference/files/retrieve-contents
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Training_File;

    /**
      The file ID used for validation. You can retrieve the validation results with the Files API:
      https://platform.openai.com/docs/api-reference/files/retrieve-contents
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Validation_File;
};

USTRUCT(BlueprintType)
struct FListFineTuningJobsResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FFineTuningJobObjectResponse> Data;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Has_More{false};
};

USTRUCT(BlueprintType)
struct FFineTuningJobEventResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created_At{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Level;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Message;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;
};
