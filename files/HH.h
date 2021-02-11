UCLASS()
class CCREFLECTION_API UHH : public UObject
{
	PRAGMA_DISABLE_DEPRECATION_WARNINGS
public:
	static void execHHFunc( UObject* Context, FFrame& Stack, void *const Z_Param__Result);
	static void execHHFunc( UObject* Context, FFrame& Stack, void *const Z_Param__Result);
private:
	PRAGMA_ENABLE_DEPRECATION_WARNINGS

private:
	static void StaticRegisterNativesUHH();
	friend struct Z_Construct_UClass_UHH_Statics;
public:
	private:
    UHH& operator=(UHH&&); 
    UHH& operator=(const UHH&); 
	NO_API static UClass* GetPrivateStaticClass(); 
public:  
	/** Bitwise union of #EClassFlags pertaining to this class.*/  
	enum {StaticClassFlags=COMPILED_IN_FLAGS(0)};  
	/** Typedef for the base class ({{ typedef-type }}) */  
	typedef UObject Super; 
	/** Typedef for {{ typedef-type }}. */  
	typedef UHH ThisClass; 
	/** Returns a UClass object representing this class at runtime */  
	inline static UClass* StaticClass()  
	{  
		return GetPrivateStaticClass();  
	}  
	/** Returns the package this class belongs in */  
	inline static const TCHAR* StaticPackage()  
	{  
		return TEXT("/Script/CCReflection");  
	}  
	/** Returns the static cast flags for this class */  
	inline static EClassCastFlags StaticClassCastFlags()  
	{  
		return CASTCLASS_None;  
	}  
	/** For internal use only; use StaticConstructObject() to create new objects. */  
	inline void* operator new(const size_t InSize, EInternal InInternalOnly, UObject* InOuter = (UObject*)GetTransientPackage(), FName InName = NAME_None, EObjectFlags InSetFlags = RF_NoFlags)  
	{  
		return StaticAllocateObject(StaticClass(), InOuter, InName, InSetFlags);  
	}  
	/** For internal use only; use StaticConstructObject() to create new objects. */  
	inline void* operator new( const size_t InSize, EInternal* InMem )  
	{  
		return (void*)InMem;  
	}

	friend FArchive &operator<<( FArchive& Ar, UHH*& Res ) \
	{ \
		return Ar << (UObject*&)Res; \
	} \
	friend void operator<<(FStructuredArchive::FSlot InSlot, UHH*& Res) \
	{ \
		InSlot << (UObject*&)Res; \
	}

public:
	UFUNCTION(BlueprintCallable)
	int HHFunc(int a);

	UPROPERTY()
	int HHID;
};