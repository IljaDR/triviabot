/************************************************************************************
 *
 * TriviaBot, The trivia bot for discord based on Fruitloopy Trivia for ChatSpike IRC
 *
 * Copyright 2004 Craig Edwards <support@brainbox.cc>
 *
 * Core based on Sporks, the Learning Discord Bot, Craig Edwards (c) 2019.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ************************************************************************************/

#pragma once
#include <string>

#define BACKEND_HOST "triviabot.co.uk"

using json = nlohmann::json;

// Represents the current streak data for a guild
struct streak_t
{
	int32_t personalbest;
	int64_t topstreaker;
	int32_t bigstreak;
};

void set_io_context(class asio::io_context* ioc, const std::string &apikey);

// These functions fetch questions via the REST API
std::vector<std::string> fetch_question(int64_t id, int64_t guild_id);
std::vector<std::string> fetch_shuffle_list(int64_t guild_id, const std::string &category = "");
std::vector<std::string> fetch_insane_round(int64_t &question_id, int64_t guild_id);

// These functions used to query the REST API but are more efficient doing direct database queries.
void update_score_only(int64_t snowflake_id, int64_t guild_id, int score, int64_t channel_id);
int32_t update_score(int64_t snowflake_id, int64_t guild_id, time_t recordtime, int64_t id, int score);
int32_t get_total_questions();
std::vector<std::string> get_top_ten(uint64_t guild_id);
std::string get_current_team(int64_t snowflake_id);
void leave_team(int64_t snowflake_id);
streak_t get_streak(int64_t snowflake_id, int64_t guild_id);
bool check_team_exists(const std::string &team);
void add_team_points(const std::string &team, int points, int64_t snowflake_id);
int32_t get_team_points(const std::string &team);

// These functions query the REST API and are not as performant as the functions above. Some of these cannot
// currently be rewritten as direct queries, as they use external apis like neutrino, or are hooked into the
// achievement system, or are REST by design such as those that use graphics APIs.
bool join_team(int64_t snowflake_id, const std::string &team, int64_t channel_id);
void change_streak(int64_t snowflake_id, int64_t guild_id, int score);
std::string create_new_team(const std::string &teamname);
void cache_user(const class aegis::user *_user, const class aegis::guild *_guild, const class aegis::user::guild_info* gi);
void send_hint(int64_t snowflake_id, const std::string &hint, uint32_t remaining);
std::string custom_command(const std::string &command, const std::string &parameters, int64_t user_id, int64_t channel_id, int64_t guild_id);
void log_game_start(int64_t guild_id, int64_t channel_id, int64_t number_questions, bool quickfire, const std::string &channel_name, int64_t user_id, const std::vector<std::string> &questions, bool hintless);
void log_game_end(int64_t guild_id, int64_t channel_id);
bool log_question_index(int64_t guild_id, int64_t channel_id, int32_t index, uint32_t streak, int64_t lastanswered, int32_t state);
json get_active(const std::string &hostname, int64_t cluster_id);
std::vector<std::string> get_api_command_names();
json get_num_strs();
