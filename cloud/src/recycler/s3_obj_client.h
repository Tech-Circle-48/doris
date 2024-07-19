// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <memory>

#include "recycler/obj_storage_client.h"

namespace Aws::S3 {
class S3Client;
} // namespace Aws::S3

namespace doris::cloud {

class S3ObjClient final : public ObjStorageClient {
public:
    S3ObjClient(std::shared_ptr<Aws::S3::S3Client> client, std::string endpoint)
            : s3_client_(std::move(client)), endpoint_(std::move(endpoint)) {}
    ~S3ObjClient() override;

    ObjectStorageResponse put_object(ObjectStoragePathRef path, std::string_view stream) override;

    ObjectStorageResponse head_object(ObjectStoragePathRef path, ObjectMeta* res) override;

    std::unique_ptr<ObjectListIterator> list_objects(ObjectStoragePathRef path) override;

    ObjectStorageResponse delete_objects(const std::string& bucket, std::vector<std::string> keys,
                                         ObjClientOptions option) override;

    ObjectStorageResponse delete_object(ObjectStoragePathRef path) override;

    ObjectStorageResponse delete_objects_recursively(ObjectStoragePathRef path,
                                                     ObjClientOptions option,
                                                     int64_t expiration_time = 0) override;

    ObjectStorageResponse get_life_cycle(const std::string& bucket,
                                         int64_t* expiration_days) override;

    ObjectStorageResponse check_versioning(const std::string& bucket) override;

private:
    std::shared_ptr<Aws::S3::S3Client> s3_client_;
    std::string endpoint_;
};

} // namespace doris::cloud