// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#include "UxtTooltipSpawnerComponentVisualizer.h"
#include "Tooltips/UxtTooltipActor.h"
#include "Tooltips/UxtTooltipSpawnerComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SceneManagement.h"
#include "UXToolsEditor.h"
#include "Utils/UxtMathUtilsFunctionLibrary.h"
#include "Components/WidgetComponent.h"

void FUxtTooltipSpawnerComponentVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	const UUxtTooltipSpawnerComponent* TooltipSpawner = Cast<const UUxtTooltipSpawnerComponent>(Component);
	if (TooltipSpawner == nullptr)
		return;

	const auto LineColor = FLinearColor::White;

	const AActor* Owner = TooltipSpawner->GetOwner();
	const FVector Offset = TooltipSpawner->Pivot->GetRelativeLocation() * Owner->GetActorScale3D();
	const FVector LineStart = TooltipSpawner->GetOwner()->GetActorLocation();
	const FVector LineEnd = LineStart + Offset;
	const float LineThickness = 0.05f;
	PDI->DrawLine(LineStart, LineEnd, LineColor, SDPG_Foreground, LineThickness);

	constexpr float Width = 10.0f;
	constexpr float Height = 10.0f;
	constexpr float Depth = 0.0f;
	FTransform Transform = TooltipSpawner->GetOwner()->GetActorTransform();
	Transform.SetLocation(Transform.GetLocation() + Offset);

	const FVector Vertices[] =
	{
		FVector(-Depth, Width, Height),
		FVector(-Depth, Width, -Height),
		FVector(-Depth, -Width, -Height),
		FVector(-Depth, -Width, Height)
	};

	for (int i = 0; i < 4; ++i)
	{
		// No scale because we don't want the scale of the target to affect the preview.
		const FVector Start = Transform.TransformPositionNoScale(Vertices[i]);
		const FVector End = Transform.TransformPositionNoScale(Vertices[(i + 1) % 4]);
		PDI->DrawLine(Start, End, LineColor, SDPG_Foreground, LineThickness);
	}
}