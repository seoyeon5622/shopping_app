# 🛒 C언어 기반 쇼핑몰 관리 프로그램

OpenWeather API를 연동하여 실시간 날씨 정보를 제공하고, 관리자와 구매자 모드를 분리하여 상품 관리 및 쇼핑 기능을 제공하는 C언어 프로젝트입니다.

## <주요 기능>
1. 실시간 날씨 정보 제공
   - API 연동: OpenWeather API를 사용하여 서울의 현재 기온을 실시간으로 가져옵니다.
   - 쇼핑 가이드: 사용자에게 현재 기온을 출력하여 옷 구매에 참고할 수 있도록 돕습니다.
  
2. 관리자 모드
   - 보안: 설정된 비밀번호(1234)를 입력해야 진입 가능합니다.
   - 상품 등록: 새로운 상품 이름과 가격을 입력하여 products.txt 파일에 저장합니다.
   - 상품 삭제: 파일 내의 특정 상품을 선택하여 제거할 수 있습니다. (임시 파일 활용 로직)

3. 구매자 모드
   - 상품 목록 조회: 현재 판매 중인 모든 상품 리스트를 확인합니다.
   - 키워드 검색: strstr 함수를 이용해 상품명의 일부만 입력해도 관련 상품을 모두 찾아냅니다.
   - 장바구니 시스템: Vector 자료구조(동적 배열)를 직접 구현하여 상품을 담고 관리합니다.
   - 결제: 장바구니에 담긴 총 금액을 계산하고 목록을 초기화합니다.

## <프로젝트 구조>
main.c: 프로그램의 메인 루프 및 모드 선택 로직

header/product/: 상품 정보 정의, 추가, 조회, 검색 기능

header/cart/: 장바구니 아이템 정의 및 추가/삭제/결제 로직

header/vector/: void*를 이용한 범용 동적 배열(Vector) 구현

header/weather/: libcurl을 이용한 외부 API 통신 및 JSON 파싱

## <실행 방법>
### 사전 요구 사항
libcurl: 날씨 API 통신을 위해 필요합니다.

C 컴파일러: gcc 또는 clang

### 컴파일 및 실행 (macOS/Linux)

터미널에서 아래 명령어를 입력하세요:

`cc main.c header/product/product.c header/cart/cart.c header/vector/vector.c header/weather/weather.c -o shopping_app -lcurl
`

`./shopping_app`
