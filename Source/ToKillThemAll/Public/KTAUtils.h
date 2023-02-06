
class KTAUtils
{
  public:
    template <typename T> static T *GetKTAPlayerComponent(APawn *PlayerPawn)
    {
        if (!PlayerPawn)
            return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }
};