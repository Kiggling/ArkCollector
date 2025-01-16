# Win API 프로젝트 - Ark Collector
1. [주제](#주제)
2. [인원](#인원)
3. [시연 영상](#시연-영상)
4. [개발 기간](#개발-기간)
5. [게임 구성](#게임-구성)
6. [게임 시나리오](#게임-시나리오)
7. [클래스 구성](#클래스-구성)
8. [코드 컨벤션](#코드-컨벤션)
9. [커밋 컨벤션](#커밋-컨벤션)
8. [리소스](#리소스)
## 주제
레이드 만들기.

## 인원
- [조성환](https://github.com/rnrn213)
- [장우현](https://github.com/dngus1683)

## 시연 영상
[유튜브](https://youtu.be/kwFxH_ZBNbI)

## 개발 기간
2024.11.25 ~ 2025.01.15

## 게임 구성
- **View**: 2D 탑 뷰
- **해상도**: 1440 x 900
- **맵 크기**: 1440 x 900

## 게임 시나리오
    - 시작화면
        - 시작 버튼
        - 종료 버튼
    - 게임 레이드 화면
        - 플레이어
            - 스킬 창
            - 체력 / 마나 창
            - 스킬 사용
        - 보스
            - 보스 체력
            - 패턴
            - 기믹
    - 딜 지분 화면
    - 엔딩 크레딧

## 클래스 구성
### Engine
    - Applicaiton
        - GameManager
            - Game
                - SceneManager
                    - Scene
                        - Layer
                            - GameObject
                                - Component
                                    - Transform
                                    - Script
                                    - Collider
                                    - Rigidbody
                                    - Camera
                                    - SpriteRenderer
                                    - TilemapRenderer
                                    - Animator

### Contents
    - Player
        - Player 객체
        - Player Script
    - Boss
        - Boss 객체
        - Boss Script
    - Scene
        - Load
            - LoadResource
            - LoadScene
        - 플레이 화면

## 코드 컨벤션
1. **파일 이름 및 구조**
    - 클래스 파일 이름: 클래스명.h, 클래스명.cpp
        - 예: PlayerCharacter.h, PlayerCharacter.cpp
    - 프리픽스 사용: 특정 타입에 따라 프리픽스 사용
        - 클래스: 없음
        - 구조체: F
        - 열거형: E
        - 템플릿: T
    - 서픽스 사용: 특정 역할에 따라 서픽스 사용
        - 컴포넌트: Component

2. **네이밍 규칙**
    - CamelCase 사용 (첫 글자 대문자).
    - 멤버 변수: m 접두사 + CamelCase
        - 예: mHealth, mPlayerName
    - 함수: 동사형 + CamelCase
        - 예: MoveForward(), GetHealth()
    - 로컬 변수: 소문자 + CamelCase
        - 예: currentHealth, playerIndex
    - Boolean 변수: b 접두사
        - 예: bIsDead, bHasKey

4. **들여쓰기 및 공백**
    - 탭 대신 스페이스 4칸 사용.
    - 함수와 함수 사이에는 한 줄 공백 삽입.
    - 중괄호 {}는 한 줄 내려서 사용.

5. **조건문 조건 변수**
    - 조건문 안의 조건의 길이가 길면 변수화 하여 사용.
    ``` c++
    if(mPosition.x > 0 && mPosition.x < width &&  mPosition.y > 0 && mPosition.y < height)
    {
        // ...
    }
    ```
    ``` c++
    bool bIsInXBoundary = mPosition.x > 0 && mPosition.x < width;
    bool bIsInYBoundary = mPosition.x > 0 && mPosition.x < width;

    if(bIsInXBoundary &&  bIsInYBoundary)
    {
        // ...
    }
    ```

## 커밋 컨벤션
커밋 메세지는 크게 **제목(Header)**, **본문(Body)**, **푸터(Footer)**로 구성되며, 각 부분에 대해 다음과 같은 컨벤션을 따른다.

### **1. 제목 (Header)**

- **간결하게 작성**: 제목은 50자 이내로 간결하게 작성한다.
- **대문자로 시작**: 제목을 영어로 작성 시, 첫 글자는 항상 대문자로 시작한다.
- **마침표 생략**: 제목 끝에 마침표나 기타 종결 부호를 사용하지 않는다.
- **명령형으로 작성**: 제목을 영어로 작성 시, "Fix bug"와 같이 명령형으로 작성한다.
- **현재 시제로 작성**: 현재 시제를 사용해 작성한다.

| Type | 설명 | 예시 |
| --- | --- | --- |
| feat | 새로운 기능을 추가할 때 사용 | `feat: Add user authentication module` |
| fix | 버그를 수정할 때 사용 | `fix: Correct login button alignment` |
| docs | 문서에 변경이 있을 때 사용 | `docs: Update API documentation` |
| style | 코드의 스타일을 수정할 때 사용 (포맷팅, 세미콜론 추가 등) | `style: Format code according to ESLint` |
| refactor | 코드 리팩토링 (기능 변경 없이 코드 구조만 개선) | `refactor: Simplify user authentication logic` |
| perf | 성능을 향상시키는 코드 변경 | `perf: Optimize image loading speed` |
| test | 테스트 코드 추가 또는 수정 시 사용 | `test: Add unit tests for login module` |
| chore | 빌드 작업, 패키지 매니저 설정 등 기타 변경 시 사용 | `chore: Update dependencies` |
| ci | CI 관련 설정이나 스크립트를 수정할 때 사용 | `ci: Update CircleCI configuration` |
| build | 빌드 시스템 또는 외부 종속성에 영향을 미치는 변경 시 사용 | `build: Update webpack configuration` |
| revert | 이전 커밋을 되돌릴 때 사용 | `revert: Revert "Add user authentication module"` |
| release | 새 버전을 릴리스할 때 사용 | `release: 1.0.0` |

### **본문 (Body)**

- **선택 사항**: 본문은 필수 사항이 아니며, 필요할 때만 작성한다.
- **줄 바꿈**: 한 줄에 72자를 넘지 않도록 줄 바꿈을 한다.
- **상세 설명**: 제목만으로 설명하기 어려운 내용을 구체적으로 서술한다. 변경 이유나 변경 사항이 미치는 영향을 설명하는 데 중점을 둔다.

### **3. 푸터 (Footer)**

- **선택 사항**: 푸터 역시 필요할 때만 작성한다.
- **이슈 연동**: 이슈 트래커와 연동이 필요한 경우, `Fixes #42`와 같이 이슈 번호를 명시해 자동으로 이슈를 닫을 수 있다.
- **브레이킹 체인지**: 코드 변경이 이전 버전과 호환되지 않는 중대한 변경사항을 포함할 때, `BREAKING CHANGE:`로 시작하여 설명을 추가한다.

> 예시: Fixes #42
> 
> 
> `BREAKING CHANGE: Changed API endpoint from /v1 to /v2`

## 리소스 
- [https://itch.io/search?q=Lucifer](https://itch.io/search?q=Lucifer)
