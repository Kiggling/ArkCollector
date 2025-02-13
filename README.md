# Win API 프로젝트 - Ark Collector

1. [주제](#주제)
2. [시나리오](#시나리오)
3. [인원](#인원)
4. [시연 영상](#시연-영상)
5. [개발 기간](#개발-기간)
6. [게임 구성](#게임-구성)
7. [클래스 구성](#클래스-구성)
8. [콘텐츠 소스 구현 리뷰](#콘텐츠-소스-구현-리뷰)
9. [코드 컨벤션](#코드-컨벤션)
10. [커밋 컨벤션](#커밋-컨벤션)
11. [리소스](#리소스)

## 주제
여러 가지 기믹을 구사하는 보스 레이드 만들기.

## 시나리오
- [보스 시나리오](https://github.com/Kiggling/ArkCollector/blob/master/Plan/BossRaidSenario.md)
- [플레이어 시나리오](https://github.com/Kiggling/ArkCollector/blob/master/Plan/PlayerSenario.md)

## 인원
- [조성환](https://github.com/rnrn213)
- [장우현](https://github.com/dngus1683)

## 시연 영상
[![image](https://github.com/user-attachments/assets/85d10095-204d-4a20-94ce-2204d193cc0c)](https://youtu.be/kwFxH_ZBNbI)

## 개발 기간
2024.11.25 ~ 2025.01.15

## 게임 구성
- **View**: 2D 탑 뷰
- **해상도**: 1440 x 900
- **맵 크기**: 1440 x 900

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
    - Projectile
        - Projectile 객체
        - Projectile Script
    - Wall
        - Wall 객체
        - WallS Script
    - Scene
        - Load
            - LoadResource
            - LoadScene
        - 플레이 화면

# 콘텐츠 소스 구현 리뷰
### Boss

- 보스 객체를 표현하는 클래스다.
- GameObject를 상속받은 클래스다.
- 보스의 HP0 기믹 때, 보스와 똑같이 생긴 3개의 보스 환영이 생성되는데, 이를 위해 Boss 클래스와 부속 보스 컴포넌트 클래스를 재사용하기 위해 `bool mbIsIllusion;` 의 bool 값을 갖는다.

### BossScriptComponent

- 보스의 상태를 부여하여, 현재 상태에 해당하는 함수를 호출하는 방식으로 보스를 제어한다.
    - 보스의 상태는 총 8가지로 설정한다.
        - **Idle**
            - 보스가 가만히 있는 상태.
            - 보스가 공격을 할 지, 플레이어 위치로 순간이동을 할 지를 매번 판단.
            - Idle 상태로 1.5초 유지한다면 Walk 상태로 전환.
        - **Walk**
            - 보스가 플레이어를 향해서 걷는 상태.
            - 걷는 방향은 플레이어를 타겟으로 설정하여 해당 위치와 보스의 현재 위치 간의 차이를 구해 정규화함.
            - 보스가 공격을 할 지, 플레이어 위치로 순간이동을 할 지를 매번 판단.
            - Walk 상태로 3초 유지한다면 Idle 상태로 전환.
        - **Jump**
            - 보스가 점프를 한 상태.
            - Idle 또는 Walk 상태에서 보스가 가장 최근에 공격을 한 후 지난 시간이 6초가 지나면 플레이어에게 순간이동 함.
            - 순간이동의 순서는 Jump → None → Land.
            - Jump는 제자리에서 점프함.
            - Jump 상태에서 Jump의 애니메이션이 끝나면, 애니메이션을 정지 후 보스의 위치를 플레이어의 위치로 설정하고 콜라이더를 비활성화함.
            - None 상태로 전환.
        - **None**
            - 보스가 점프를 한 후 화면에서 사라진 상태.
            - 보스가 사라진 후 1초가 지나면 Land 애니메이션과 착지 시 모래바람을 연출하는 이펙트를 재생하고 Land 상태로 전환.
        - **Land**
            - 보스가 땅에 착지한 상태.
            - 비활성화 했던 콜라이더를 활성화함.
            - Land 애니메이션의 재생이 끝나면 Walk 상태로 전환.
        - **Attack**
            - 보스가 공격하는 상태.
            - Idle 또는 Walk 상태에서 보스와 플레이어 사이의 거리가 100.f보다 작고 보스의 가장 최근의 공격 이후 3초가 지났다면, Attack 상태로 전환.
            - 공격 타입은 총 3가지로 나뉨.
            - `rand()` 함수를 통해 랜덤으로 공격 타입을 가짐.
            - 정해진 공격 타입에 맞는 애니메이션 수행
                - **공격 타입 1**: 플레이어의 방향으로 작은 검기 발사체 생성.
                - **공격 타입 2:** 보스 기준 상하좌우로 큰 검기를 여러 차례 날림.
                - **공격 타입 3**: 보스 기준으로 랜덤한 위치에 낙하물을 여러 개 생성함. 이때 낙하물의 생성 주기는 sin 함수를 사용해 적용.
            - 한 번의 공격이 끝나면 Idle 상태로 전환.
        - **Hurt**
            - 보스가 플레이어에게 맞은 상태.
            - `OnCollisionEnter()` 함수를 통해, 플레이어의 발사체와 보스가 충돌할 때, 보스가 Attack 또는 Gimmick 상태가 아니라면 Hurt 상태로 전환.
            - Hurt 애니메이션 재생이 완료되면 Idle 상태로 전환.
        - **Death**
            - 보스가 죽은 상태.
            - 보스의 체력이 0이 되었을 때 마지막 Gimmick을 통해 최종 체력이 0이 되면 Death 상태로 전환.
            - Death 애니메이션 재생 후 보스의 콜라이더를 비활성화.
            - 영구적으로 Death 상태 유지.
        - **Gimmick**
            - **Gimmick 체크 및 관리**:
                - `checkGimmick()` 메서드를 통해 보스의 상태에 따라 `HP100`, `HP200`, `HP0`의 Gimmick을 설정하고 상태를 결정.
                - 이때, 체력으로만 기믹을 설정하면 기믹이 발생하지 않고 넘어갈 수 있기 때문에, 각각의 기믹을 순서대로 수행했는지를 체크하는 mGimmickCheck bitset을 사용.
            - **Gimmick 처리**:
                - 각 Gimmick 상태는 `gimmickHP100`, `gimmickHP200`, `gimmickHP0`로 구분.
                - Gimmick의 세부 상태는 `eGimmickState`로 관리하며, `None`, `Jump`, `Land`, `Wait`, `Attack`, `End` 등으로 진행.
            - **HP200**
                1. **None**: 1초 대기 후 랜턴(`Lamp`) 활성화.
                2. **Jump**: 보스 위치를 화면 중앙으로 이동.
                3. **Land**: 2초 대기 후 Idle 상태로 복귀.
                4. **Wait**: 랜턴 중 하나를 안전 구역으로 설정 후 6초 대기.
                5. **Attack**: 이펙트를 발생시키고 Gimmick 종료.
            - **HP100**
                1. **None**: 1초 대기 후 Land 상태로 변경.
                2. **Jump**: 화면 중앙으로 이동.
                3. **Land**: 애니메이션 및 `createWall()` 을 통해 벽 생성.
                4. **Wait**: 6초 대기 후 플레이어가 위치한 방향으로 공격 이펙트 발사.
                5. **Attack**: Idle 상태로 복귀 후 Gimmick 종료.
            - **HP0**
                - HP0 기믹에서는 보스의 콜라이더가 활성화 되어 있다.
                - 이때 플레이어의 공격은 보스의 체력을 낮추지 않고 보스의 **mLastHP**를 낮춘다.
                - **mLastHP**가 0이 되면 Death 상태로 전환한다.
                - **순서**:
                    1. **None**: 1초 대기 후 Land 상태로 변경.
                    2. **Jump**: 맵 중앙 기준 상하좌우의 위치 중 랜덤한 곳으로 보스 위치 변경 및 나머지 위치에 환영(Illusion) 생성.
                    3. **Land**: 애니메이션 실행 후 Wait 상태로 변경.
                    4. **Wait**: 3개의 환영과 보스의 x좌표값에 변화를 줘서 흔들림 구현. 이때 보스와 환영의 흔들림 속도를 다르게 설정. 환영 동작 수행 후 Gimmick 종료.

### BossStatComponent

- 보스의 체력 정보를 갖는 컴포넌트다.
- 기본 보스의 최대 체력 정보와 실시간 보스 체력 수치를 관리한다.
- 보스의 체력이 0이 되었을 때, 마지막 기믹 수행에 사용되는 **mLastHP**를 추가로 갖는다.

### Wall

- 보스의 HP100 기믹 때 사용되는 벽 객체다.
- 해당 기믹 때 플레이어의 안전지대를 담당한다.
- **ELayerType**이 **Object**로 설정된다.
- **ELayerType Object**와 **Player** 간의 충돌 검사를 true로 하여 충돌을 판단한다.
- 벽이 생성되는 위치에 따라 재생되는 애니메이션의 방향이 정해지기 때문에 `eDirection mDirection;`  값을 갖는다.

### WallScriptComponent

- 벽은 **Build**와 **Destroy** 두 가지 상태를 갖는다.

    - **Build**
        - **BossScriptComponent**에서 벽이 생성되는 애니메이션이 재생되며, **WallScriptComponent**가 생성될 때 자동으로 **Build** 상태를 갖음.
        - 벽이 생성되고 7초 후, 벽이 무너지는 애니메이션이 재생되고 Destroy 상태로 전환.
    - **Destroy**
        - 벽이 무너지는 애니메이션 재생이 완료되면 Wall 객체를 제거.

### Projectile

- 보스와 플레이어가 생성하는 발사체와 이펙트를 담당하는 클래스다.
- 발사되는 위치와 발사 범위, 발사 속도 정보를 갖는다.

### ProjectileScriptComponent

- 발사체의 스크립트를 담당하는 컴포넌트다.
- 발사체가 표현되는 타입(**mEffectType**)과 대미지 타입(**mDamageType**)의 정보를 갖는다.
- **mEffectType**
    - **Projectile**과 **Effect** 두 가지  타입이 있다.
        - 발사체가 특정 방향으로 이동하는(발사되는) 타입이라면 **Projectile**.
            - 매 업데이트마다 발사체의 현재 위치와 발사 발사 시작 위치 간의 거리를 계산.
            - 계산한 거리가 발사체의 발사 범위를 넘어서거나 맵 범위를 넘어서면, 발사체 객체 제거.
            - 발사체의 위치를 **속도 * 시간**만큼 더해서 현재 위치 업데이트.
            - **ex)** 보스의 검기, 플레이어의 화살
        - 발사체가 제자리에서만 애니메이션이 재생된 후 사라지는 타입이라면 **Effect**.
            - 애니메이션 재생이 완료되면 객체 제거.
            - **ex)** 보스의 Land 애니메이션 시 발생하는 먼지
- **mDamgeType**
    - `OnCollisionEnter()` 발생 시 타입에 따라 코드를 나누었다.
    - 일단 충돌한 대상의 StatComponent를 통해 대상의 체력을, 발사체의 대미지만큼 줄인다.
    - `dynamic_cast<Boss*>()`를 통해, 충돌 대상이 보스인지 확인 후, 보스가 맞고 보스의 현재 상태가 **HP0 Gimmick**이라면 보스의 **Hp** 대신 **mLastHP**를 줄이도록 한다.
    - **Projectile**과 **Effect** 두 가지  타입이 있다.
        - 발사체가 공격 대상과 충돌함과 동시에 제거되는 타입이라면 **Projectile**.
            - **Projectile** 타입이라면 `OnCollisionEnter()`에서 즉시 발사체 객체 제거.
            - **ex)** 플레이어의 화살, 보스의 낙하물
        - 발사체가 공격 대상과 충돌해도 사라지지 않고 정해진 범위까지 재생되는 타입이라면 **Effect**.
            - `OnCollisionEnter()`에서 제거되지 않음. ⇒ 오로지 `Update()` 에서 제거 유뮤 판단.
            - **ex)** 보스의 검기


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
