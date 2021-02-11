#include "UObject/GeneratedCppIncludes.h"
#include "CCReflection/HH.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHH() {}
// Cross Module References
	CCREFLECTION_API UClass* Z_Construct_UClass_UHH_NoRegister();
	CCREFLECTION_API UClass* Z_Construct_UClass_UHH();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_CCReflection();
// End Cross Module References

static void execHHFunc( UObject* Context, FFrame& Stack, void *const Z_Param__Result) 
{
    FIntProperty::TCppType Z_Param_a = FIntProperty::GetDefaultPropertyValue();
    Stack.StepCompiledIn<FIntProperty>(&Z_Param_a);
    
    Stack.Code += !!Stack.Code;
    { 
        SCOPED_SCRIPT_NATIVE_TIMER(ScopedNativeCallTimer);
        *(int32*)Z_Param__Result = (UHH *) Context->HHFunc(Z_Param_a);
    }
}

void UHH::StaticRegisterNativesUHH()
{
	UClass* Class = UHH::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "HHFunc", &UHH::execHHFunc },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
struct Z_Construct_UFunction_UHH_HHFunc_Statics
{
	struct HH_eventHHFunc_Parms
	{
		int32 a;
		int32 ReturnValue;
	};
	static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_a;
	static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
	static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
	static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
	static const UE4CodeGen_Private::FFunctionParams FuncParams;
};
const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHH_HHFunc_Statics::NewProp_a = { "a", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HH_eventHHFunc_Parms, a), METADATA_PARAMS(nullptr, 0) };
const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHH_HHFunc_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HH_eventHHFunc_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHH_HHFunc_Statics::PropPointers[] = {
	(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHH_HHFunc_Statics::NewProp_a,
	(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHH_HHFunc_Statics::NewProp_ReturnValue,
};
#if WITH_METADATA
const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHH_HHFunc_Statics::Function_MetaDataParams[] = {
	{ "ModuleRelativePath", "HH.h" },
};
#endif
const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHH_HHFunc_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHH, nullptr, "HHFunc", nullptr, nullptr, sizeof(HH_eventHHFunc_Parms), Z_Construct_UFunction_UHH_HHFunc_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHH_HHFunc_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHH_HHFunc_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHH_HHFunc_Statics::Function_MetaDataParams)) };
UFunction* Z_Construct_UFunction_UHH_HHFunc()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHH_HHFunc_Statics::FuncParams);
	}
	return ReturnFunction;
}
UClass* Z_Construct_UClass_UHH_NoRegister()
{
	return UHH::StaticClass();
}
struct Z_Construct_UClass_UHH_Statics
{
	static UObject* (*const DependentSingletons[])();
	static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
	static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
	static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HHID_MetaData[];
#endif
	static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_HHID;
	static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
	static const UE4CodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UHH_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CCReflection,
};
const FClassFunctionLinkInfo Z_Construct_UClass_UHH_Statics::FuncInfo[] = {
	{ &Z_Construct_UFunction_UHH_HHFunc, "HHFunc" }, // 501624126
};
#if WITH_METADATA
const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHH_Statics::Class_MetaDataParams[] = {
	{ "Comment", "/**\n * \n */" },
	{ "IncludePath", "HH.h" },
	{ "ModuleRelativePath", "HH.h" },
};
#endif
#if WITH_METADATA
const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHH_Statics::NewProp_HHID_MetaData[] = {
	{ "ModuleRelativePath", "HH.h" },
};
#endif
const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_UHH_Statics::NewProp_HHID = { "HHID", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHH, HHID), METADATA_PARAMS(Z_Construct_UClass_UHH_Statics::NewProp_HHID_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHH_Statics::NewProp_HHID_MetaData)) };
const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHH_Statics::PropPointers[] = {
	(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHH_Statics::NewProp_HHID,
};
const FCppClassTypeInfoStatic Z_Construct_UClass_UHH_Statics::StaticCppClassTypeInfo = {
	TCppClassTypeTraits<UHH>::IsAbstract,
};
const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UHH_Statics::ClassParams = {
	&UHH::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UHH_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UHH_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(Z_Construct_UClass_UHH_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHH_Statics::Class_MetaDataParams))
};
UClass* Z_Construct_UClass_UHH()
{
	static UClass* OuterClass = nullptr;
	if (!OuterClass)
	{
		UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UHH_Statics::ClassParams);
	}
	return OuterClass;
}

static UHHCompiledInDefer<UHH> AutoInitializeUHH(TEXT("UHH"), sizeof(UHH), 1368286490); 
UClass* UHH::GetPrivateStaticClass() 
{ 
	static UClass* PrivateStaticClass = NULL; 
	if (!PrivateStaticClass) 
	{ 
		/* this could be handled with templates, but we want it external to avoid code bloat */ 
		GetPrivateStaticClassBody( 
			StaticPackage(), 
			(TCHAR*)TEXT("UHH") + 1 + ((StaticClassFlags & CLASS_Deprecated) ? 11 : 0), 
			PrivateStaticClass, 
			StaticRegisterNativesUHH, 
			sizeof(UHH), 
			alignof(UHH), 
			(EClassFlags)UHH::StaticClassFlags, 
			UHH::StaticClassCastFlags(), 
			UHH::StaticConfigName(), 
			(UClass::ClassConstructorType)InternalConstructor<UHH>, 
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<UHH>, 
			&UHH::AddReferencedObjects, 
			&UHH::Super::StaticClass, 
			&UHH::WithinClass::StaticClass 
		); 
	} 
	return PrivateStaticClass; 
}

template<> CCREFLECTION_API UClass* StaticClass<UHH>()
{
	return UHH::StaticClass();
}
static FCompiledInDefer Z_CompiledInDefer_UClass_UHH(Z_Construct_UClass_UHH, &UHH::StaticClass, TEXT("/Script/CCReflection"), TEXT("UHH"), false, nullptr, nullptr, nullptr);

UHH::UHH(FVTableHelper& Helper) : Super(Helper) {};

PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif