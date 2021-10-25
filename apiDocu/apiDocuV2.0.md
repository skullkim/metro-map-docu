# Teamproject1 API document

모든 json응답은 아래의 common response와 같은 형태를 띄고 있기 때문에 세부 API 설명에서는 오직 key가 data인 부분만 서술한다. 이때 에러에 대한 응답의 경우 data는 빈 문자열을 가지며 그 대신 error가 에러 원인에 대한 객체를 가진다. 만약 키값 뒤에 '?'가 온다면 일부 응답에 대해 해당 값이 존재하지 않을 수 도 있다는 의미이다.

```jsx
{
  "status": number,
  "status_code": string,
  "request": {
    "path": string,
    "method": string,
    "params": object,
    "query": object,
  },
  "data": object
}
```

## 최소 비용 경로

GET /api/:pathTarget

pathTarget: cost(최소 비용) || time(최소 시간) || distance(최소 정거장)

query: startStation(type: string(3)), arriveStation(type: string(3))

parameter: pathTarget

사용처: src/components/modal/searchResultModal/SearchResultModal.js

성공(200):

```json

"data": {
  "cost": string,
  "distance": string,
  "time": string,
  "path": minPath[],
  "min_value"?: '',
  "other_value"?: {}
}

```

```jsx
minPath: 
{
  "id": number,
  "station": string
}
```

실패(400):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 최소 비용 경로(경유지)

GET /api/path/stopover/:pathTarget

pathTarget: cost(최소 비용) || time(최소 시간) || distance(최소 정거장)

query: startStation(type: string(3)), stopoverStation(type: string(3)), arriveStation(type: string(3))

parameter: pathTarget

사용처: src/components/modal/searchResultModal/SearchResultModal.js

성공(200):

```json

"data": {
  "time": string,
  "distance": string,
  "cost": string, 
  "path": minPath[]
}

```

```jsx
minPath: 
{
  "id": number,
  "station": string
}
```

실패(400):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 회원가입

POST /api/authentication/signup

body: email(string), password(string, 8자이상, 숫자, 문자, 특수문자 포함)

사용처: src/components/user/ValidateUserAccount.js

성공(201):

```jsx
"data": {
  "message": "success"
}
```

실패(400):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 회원가입 이메일 인증

GET /api/authentication/signup/email

query: key(string), id(string)

사용처: 발송된 이메일 내부

성공(200):

```jsx
"data": {
  "message": "success"
}
```

실패(403):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 회원가입 이메일 재인증

POST /api/authentication/signup/email/reauthorization

body: email(string)

사용처: src/components/user/ValidateUserAccount.js

성공(200):

```jsx
"data": {
  "message": "success"
}
```

실패(400-회원가입을 하지 않은 계정 또는 유효하지 않은 이메일 형식),

실패(409-이미 메일 인증을 한 유저):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 로그아웃

POST /api/authentication/logout

header: 'Bearer {accessToken}'

사용처:  src/components/user/Logout.js

성공(204):

```jsx
//응답 데이터 없음
```

실패:(401-유효하지 않은 Authentication 헤더 데이터 형식 또는 유효하지 않은 토큰),

실패(403-엑세스 토큰 만료)

```jsx
"data": "",
"error": {
  "message": string
}
```

## 로그인

POST /api/authentication/signin

body: email(string), password(string)

사용처: src/components/user/ValidateUserAccount.js

성공(200):

```jsx
"data": {
  "user_id": number, 
  "accessToken": string,
}
```

실패(400-유효하지 않은 이메일 형식 또는 비밀번호 형식. 또는 잘못된 비밀번호, 또는 가입하지 않은 계정),

실패(401-회원가입 인증메일 인증되지 않음):

```jsx
"data": "",
"error": {
  "message": string
}
```