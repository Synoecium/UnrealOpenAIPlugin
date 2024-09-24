// OpenAI, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChatTypes.generated.h"

UENUM(BlueprintType)
enum class EChatResponseFormat : uint8
{
    Text,
    JSON_Object
};

///////////////////////////////////////////////////////
//                 REQUEST TYPES
///////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FChatCompletionResponseFormat
{
    GENERATED_BODY()

    /**
      Must be one of text, json_object or json_schema
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Required")
    FString Type{"text"};
};

USTRUCT(BlueprintType)
struct FChatCompletion
{
    GENERATED_BODY()

    /**
      A list of messages comprising the conversation so far.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Required")
    TArray<FMessage> Messages;  //@todo: check

    /**
      ID of the model to use.
      See the model endpoint compatibility table for details on which models work with the Chat API.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Required")
    FString Model;

    /**
      Number between -2.0 and 2.0.
      Positive values penalize new tokens based on their existing frequency in the text so far,
      decreasing the model's likelihood to repeat the same line verbatim.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    float Frequency_Penalty{0.0f};

    /**
      Modify the likelihood of specified tokens appearing in the completion.
      Accepts a json object that maps tokens (specified by their token ID in the tokenizer)
      to an associated bias value from -100 to 100. Mathematically, the bias is added to
      the logits generated by the model prior to sampling.
      The exact effect will vary per model, but values between -1 and 1 should decrease
      or increase likelihood of selection; values like -100 or 100 should result in a ban
      or exclusive selection of the relevant token.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    TMap<FString, int32> Logit_Bias;

    /**
      Whether to return log probabilities of the output tokens or not.
      If true, returns the log probabilities of each output token returned in the content of message.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    bool Logprobs{false};

    /**
      An integer between 0 and 20 specifying the number of most likely tokens
      to return at each token position, each with an associated log probability.
      logprobs must be set to true if this parameter is used.

    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    int32 Top_Logprobs{0};
    // @todo: as optional
    */

    /**
      An upper bound for the number of tokens that can be generated for a completion,
      including visible output tokens and reasoning tokens.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    int32 Max_Completion_Tokens{100};

    /**
      How many chat completion choices to generate for each input message.
      Note that you will be charged based on the number of generated tokens across all of the choices.
      Keep n as 1 to minimize costs.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    int32 N{1};

    /**
      Number between -2.0 and 2.0.
      Positive values penalize new tokens based on whether they appear in the text so far,
      increasing the model's likelihood to talk about new topics.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    float Presence_Penalty{0.0f};

    /**
      An object specifying the format that the model must output.
      Setting to { "type": "json_object" } enables JSON mode,
      which guarantees the message the model generates is valid JSON.

      Important: when using JSON mode, you must also instruct the model to produce JSON yourself
      via a system or user message. Without this, the model may generate an unending stream of whitespace
      until the generation reaches the token limit, resulting in a long-running and seemingly "stuck" request.
      Also note that the message content may be partially cut off if finish_reason="length",
      which indicates the generation exceeded max_tokens or the conversation exceeded the max context length.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    FChatCompletionResponseFormat Response_Format;

    /**
      This feature is in Beta. If specified, our system will make a best effort to sample deterministically,
      such that repeated requests with the same seed and parameters should return the same result.
      Determinism is not guaranteed, and you should refer to the system_fingerprint responseparameter
      to monitor changes in the backend.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    int32 Seed{0};  // @todo: optional

    /**
      Specifies the latency tier to use for processing the request. This parameter is relevant for customers subscribed to the scale tier
    service:

    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    FString Service_Tier;
    // @todo: optional
    */

    /** Up to 4 sequences where the API will stop generating further tokens. */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    TArray<FString> Stop;

    /**
      If set, partial message deltas will be sent, like in ChatGPT.
      Tokens will be sent as data-only server-sent events as they become available,
      with the stream terminated by a data: [DONE] message.
      See the OpenAI Cookbook for example code
      [https://github.com/openai/openai-cookbook/blob/main/examples/How_to_stream_completions.ipynb]
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    bool Stream{false};

    // @todo: stream options

    /**
      What sampling temperature to use, between 0 and 2.
      Higher values like 0.8 will make the output more random, while lower values like 0.2 will make it more focused and deterministic.
      We generally recommend altering this or top_p but not both.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    float Temperature{1.0f};

    /**
      An alternative to sampling with temperature, called nucleus sampling,
      where the model considers the results of the tokens with top_p probability mass.
      So 0.1 means only the tokens comprising the top 10% probability mass are considered.
      We generally recommend altering this or temperature but not both.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    float Top_P{1.0f};

    /**
      A list of tools the model may call.
      Currently, only functions are supported as a tool.
      Use this to provide a list of functions the model may generate JSON inputs for.
      A max of 128 functions are supported.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    TArray<FTools> Tools;

    /**
      Controls which (if any) tool is called by the model.
      "none" means the model will not call any tool and instead generates a message.
      "auto" means the model can pick between generating a message or calling one or more tools.
      "required" means the model must call one or more tools.
      Specifying a particular tool via {"type": "function", "function": {"name": "my_function"}}
      forces the model to call that tool.

      none is the default when no functions are present. auto is the default if functions are present.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    FToolChoice Tool_Choice;

    /**
      Whether to enable parallel function calling during tool use.

    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    bool Parallel_Tool_Calls{true};
    // todo: optional
    */

    /**
      A unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse.
    */
    UPROPERTY(BlueprintReadWrite, Category = "OpenAI | Optional")
    FString User;
};

///////////////////////////////////////////////////////
//                 RESPONSE TYPES
///////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FDelta
{
    GENERATED_BODY()

    /**
       The contents of the chunk message.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Content{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FToolCallsDelta Tool_Calls;

    /**
       The role of the author of this message.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Role;

    /**
       The refusal message generated by the model.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Refusal;
};

USTRUCT(BlueprintType)
struct FChatChoice
{
    GENERATED_BODY()

    /**
      The reason the model stopped generating tokens.
      This will be stop if the model hit a natural stop point or a provided stop sequence,
      length if the maximum number of tokens specified in the request was reached,
      content_filter if content was omitted due to a flag from our content filters,
      or function_call if the model called a function.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Finish_Reason{};

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
       The Unix timestamp (in seconds) of when the chat completion was created.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    /**
       The model used for the chat completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model;

    /**
      The service tier used for processing the request.
      This field is only included if the service_tier parameter is specified in the request.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Service_Tier;

    /**
      This fingerprint represents the backend configuration that the model runs with.
      Can be used in conjunction with the seed request parameter to understand when
      backend changes have been made that might impact determinism.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString System_Fingerprint;

    /**
       The object type, which is always chat.completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;
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
struct FChatStreamChoice
{
    GENERATED_BODY()

    /**
       A chat completion delta generated by streamed model responses.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FDelta Delta{};

    // todo: logprobs

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

    /**
      An optional field that will only be present when you set stream_options:
      {"include_usage": true} in your request.
      When present, it contains a null value except for the last chunk which
      contains the token usage statistics for the entire request.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FUsage Usage;
};
