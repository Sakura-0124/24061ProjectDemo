import speech_recognition as sr
import sys

def recognize_speech():
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        print("请说话...")
        try:
            audio = recognizer.listen(source, timeout=5)  # 等待5秒进行语音输入
            text = recognizer.recognize_google(audio, language="zh-CN")
            print(f"识别的文字: {text}")
            return text
        except sr.UnknownValueError:
            print("无法识别语音")
            return "无法识别语音"
        except sr.RequestError as e:
            print(f"请求失败: {e}")
            return "请求失败"

if __name__ == "__main__":
    result = recognize_speech()
    sys.stdout.write(result)
