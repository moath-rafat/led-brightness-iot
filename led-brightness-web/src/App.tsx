import { useQuery } from "@tanstack/react-query";
import Loading from "./Loading";
import { queryClient } from "./main";

export default function App() {
    const { data, error, isLoading } = useQuery({
        queryKey: ["LED_Brightness"],
        queryFn: async () => {
            const res = await fetch("http://192.168.1.84/brightness");
            if (!res.ok) throw new Error("Network error");
            return res.json();
        }
    }); 

    if(isLoading) {
        return <Loading />
    }

    return <div className="flex items-center justify-center w-screen h-screen bg-gradient-to-br from-red-100 via-red-200 to-red-300">
                <div className="flex flex-col items-center justify-center bg-white shadow-2xl rounded-2xl p-12 w-80 md:w-96">
                    {error ? <p className="text-xl text-red-700 tracking-wide mb-4">
                        Couldn't connect to server
                    </p> : 
                    <>
                        <p className="text-xl text-gray-500 uppercase tracking-wide mb-4">
                            LED Brightness
                        </p>
                        <div className="flex items-center gap-4">
                            <p className="text-6xl font-extrabold text-gray-800">{data.LED_Brightness}</p>
                            <span className="text-red-500 text-5xl">%</span>
                        </div>
                    </>}
                    <button onClick={() => queryClient.invalidateQueries({ queryKey: ["LED_Brightness"] })} 
                    className="mt-6 flex items-center gap-2 px-5 py-2 rounded-lg bg-red-600 text-white font-semibold
                    transition-all duration-200 hover:bg-red-700 active:translate-y-[1px]">
                        {error? "Try again" : "Refresh"}
                    </button>
                </div>
        </div>
}
